/*
 *  MinMaxBot.cpp
 *  planetwars_cpp1
 *
 *  Created by Barry Hurley on 10/11/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "MinMaxBot.h"

#include "BaseBot.h"
#include "CaseBasedBot.h"
#include "GameState.h"
#include "InferBot.h"
#include "order.h"
#include "Planet.h"
#include "Player.h"
#include "RageBot.h"
#include "RandomBot.h"
#include "ReinforcerBot.h"
#include "Simple1Bot.h"
#include "SniperBot.h"
#include "Stats.h"
#include "Successor.h"
#include "Timer.h"
#include <iostream>
#include <limits>

uint num_minmax_nodes, num_alpha_beta_prunes;
static double TURN_TIMEOUT = 0.8;


MinMaxBot::MinMaxBot(GameState* gamestate, uint myPlayerID) :
	_gamestate(gamestate),
	_myPlayerID(myPlayerID)
{
	_myEnemyID = Player::myEnemy(_myPlayerID);
	
	_bots.push_back(new ReinforcerBot());
	_bots.push_back(new SniperBot());
	_bots.push_back(new RageBot());
	_bots.push_back(new Simple1Bot());
	//bots.push_back(new RandomBot());
	max_bots = _bots;
	
	caseBasedBot = new CaseBasedBot();
	inferBot = new InferBot(_gamestate, _myEnemyID);
	potentialEnemyTurnSuccessors = NULL;
	branchTimer = new Timer();
	nodesms_stats = new Stats();
	previous_turn_gamestate = NULL;
	
	bot_turn_timeout = TURN_TIMEOUT/_bots.size();
	std::cerr << "bots: " << _bots.size() << " bot_timeout: " << bot_turn_timeout << std::endl;
}

MinMaxBot::~MinMaxBot(){
	for(uint i=0;i<_bots.size();i++){
		delete _bots.at(i);
	}
	delete caseBasedBot;
	delete inferBot;
	delete branchTimer;
	delete nodesms_stats;
}

Orders* MinMaxBot::doTurn(){
	Orders* orders;
	//timer->SetTimeOut(TURN_TIMEOUT);
	Orders* enemysOrders = inferBot->inferOrders(_gamestate, _myEnemyID);
	if(previous_turn_gamestate!=NULL){
		caseBasedBot->addEnemyMove(previous_turn_gamestate, enemysOrders); //FIXME get memory management right when passing previous_turn_gamestate
	}
	previous_turn_gamestate = new GameState(*_gamestate);
	
	if(enemysOrders->size()>0){
		//FIXME compare the orders the enemy made against what I bots would have made
		std::cerr << "EnemyOrders " << (enemysOrders->size()) << std::endl;
		compareBotOrders(enemysOrders);
	}
	delete enemysOrders;
	std::cerr << "MinBots: " << min_bots.size() << std::endl;
	if(min_bots.empty()){
		std::cerr << "ah jayzus, min bots is empty." << std::endl;
		min_bots = _bots;
	}
	
	SavePotentialEnemyOrdersForNextTurn();
	
	num_minmax_nodes = num_alpha_beta_prunes = minmax_depth_reached = 0;
	
	//orders = minimax_decision(_gamestate);
	orders = alphabeta_decision(_gamestate);
	std::cerr << "num_minmax_nodes: " << num_minmax_nodes << " prunes: " << num_alpha_beta_prunes << " Max depth: " << minmax_depth_reached << std::endl;
	std::cerr << "Bot will make the orders:" << std::endl;
	for(uint i=0;i<orders->size();i++){
		Order* order = orders->at(i);
		_gamestate->issueOrder(order);
		std::cerr << order->source_planet_id << " -> " << order->destination_planet_id << " " << order->shipsCount << std::endl;
	}
	
	return orders;
}

void MinMaxBot::compareBotOrders(Orders *enemyOrders){
	Orders *botOrders;
	min_bots.clear();
	if(potentialEnemyTurnSuccessors){
		for(uint i=0;i<potentialEnemyTurnSuccessors->size();i++){
			botOrders = potentialEnemyTurnSuccessors->at(i)->orders;
			bool same = compareOrders(enemyOrders,botOrders);
			std::cerr << "Bot " << i << " same = " << same << std::endl;
			if(same){
				std::cerr << "Pushing bot " << i << " onto min_bots." << std::endl;
				min_bots.push_back(_bots.at(i));
			}
		}
	}
}

bool MinMaxBot::compareOrders(Orders* orders1, Orders* orders2){
	Order *o1, *o2;
	bool all_match = true;
	for(uint i=0;i<orders1->size();i++){
		bool matches_one = false;
		o1 = orders1->at(i);
		for(uint j=0;j<orders2->size();j++){
			o2 = orders2->at(j);
			if(*o1==*o2){
#ifdef DEBUG
				std::cerr << "Found matching orders: " << *o1 << " " << *o2 << std::endl;
#endif
				matches_one = true;
				break;
			}
		}
		if(!matches_one){
			all_match = false;
			break;
		}
	}
	return all_match;
}

void MinMaxBot::SavePotentialEnemyOrdersForNextTurn(){
	//FIXME no need to store successors etc, just bot number & orders
	
	// Delete stored one from previous step first
	if(potentialEnemyTurnSuccessors!=NULL) {
		for(uint i=0;i<potentialEnemyTurnSuccessors->size();i++){
			delete (potentialEnemyTurnSuccessors->at(i));
		}
		potentialEnemyTurnSuccessors->clear();
		delete potentialEnemyTurnSuccessors;
	}
	potentialEnemyTurnSuccessors = stateSuccessors(_gamestate, _myEnemyID, _bots);
#ifdef DEBUG
	for(uint i=0;i<potentialEnemyTurnSuccessors->size();i++){
		std::cerr << "Bot " << i << ". Orders:" << std::endl;
		Orders* temp_orders = potentialEnemyTurnSuccessors->at(i)->orders;
		//std::cerr << temp_orders << " " << temp_orders->size() << std::endl;
		for(uint j=0;j<temp_orders->size();j++){
			std::cerr << *(temp_orders->at(j)) << std::endl;
		}
		std::cerr << std::endl;
	}
#endif
}

Orders* MinMaxBot::alphabeta_decision(GameState *gamestate){
	Successors* successors = stateSuccessors(gamestate, PLAYER_1, max_bots);
	Successor* max_successor = NULL, *temp_successor;
	Timer totalTimeTimer;
	totalTimeTimer.SetTimeOut(1000);
	
	int max_successor_value=std::numeric_limits<int>::min(), temp_value; //FIXME
	uint num_minmax_nodes_difference, micros_elapsed, branch_timeout;
	double nodes_ms;
	//minmax_depth_limit = 8; // d = a^(log(a,nodes)/b)
	std::cerr << "Current state util: " << utility_value(gamestate) << std::endl;
	
	for(uint i=0;i<successors->size();i++){
		branchTimer->SetTimeOut(bot_turn_timeout);
		temp_successor = successors->at(i);
		branch_timeout = bot_turn_timeout*1000.0;
		if((successors->size()-i)>0){
			uint temp_branch_timeout = (TURN_TIMEOUT*1000000.0 - totalTimeTimer.MicrosElapsed()) / (successors->size()-i);
			if(temp_branch_timeout<branch_timeout) branch_timeout=temp_branch_timeout;
			std::cerr << "branch_timeout: " << branch_timeout << std::endl;
		}
		minmax_depth_limit = calculateMinMaxDepthLimit(branch_timeout);
		//std::cerr << "minmax_depth_limit: " << minmax_depth_limit << std::endl;
		num_minmax_nodes_difference = num_minmax_nodes;
		temp_value = min_value(temp_successor->gamestate, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
		num_minmax_nodes_difference = num_minmax_nodes - num_minmax_nodes_difference;
		micros_elapsed = branchTimer->MicrosElapsed();
		//std::cerr << "num_minmax_nodes processed: " << num_minmax_nodes_difference << " time: " << micros_elapsed;
		if(micros_elapsed>0){
			nodes_ms = ((double)num_minmax_nodes_difference/((double)micros_elapsed/1000.0));
			//std::cerr << " nodes/ms: " << nodes_ms;
			nodesms_stats->addValue(nodes_ms);
			//std::cerr << " new average: " << nodesms_stats->getAverage();
		}
		//std::cerr << std::endl;

		std::cerr << "Bot " << i << " num_minmax_nodes: " << num_minmax_nodes << " prunes: " << num_alpha_beta_prunes << " Max depth: " << minmax_depth_reached << std::endl;
		
		if(temp_value>max_successor_value || (temp_value==max_successor_value && tiebreakUpdateMaxSuccessor(max_successor, temp_successor))){
			max_successor_value = temp_value;
			max_successor = temp_successor;
		}
	}
	for(uint i=0;i<successors->size();i++){
		temp_successor = successors->at(i);
		if(temp_successor!=max_successor){
			//delete temp_successor->gamestate;
			//delete temp_successor->orders;
			delete temp_successor;
		}
	}
	successors->clear();
	delete successors;
	//FIXME, leaking max_successor.gamestate
	return max_successor->orders;
}

bool MinMaxBot::tiebreakUpdateMaxSuccessor(Successor *max_successor, Successor *candidate){
	// This function gets called if both successors have equal utility values and this function acts
	// as a tie breaker to decide if this set of moves is possibly better.
	return candidate->orders->size()>max_successor->orders->size(); // Simple # of orders comparison.
}

uint MinMaxBot::calculateMinMaxDepthLimit(long long microseconds){
	uint num_nodes = nodesms_stats->getAverage()*microseconds;
	if(num_nodes==0) return 6; // Average stats will be 0 on first turn.
	uint depth = exp(log(num_nodes)/_bots.size()); // d = e^(ln(nodes)/b)
#ifdef DEBUG
	std::cerr << "Nodes: " << num_nodes << " " << nodesms_stats->getAverage() << " log(num_nodes):" << log(num_nodes) << " /botssize:" << log(num_nodes)/_bots.size() << " exp: " << exp(log(num_nodes)/_bots.size()) <<  " Depth(" << microseconds << "): " << depth << std::endl;
#endif
	return depth;
}

void printIndent(int indent){
	for(int i=0;i<indent;i++) std::cerr << "  ";
}

int MinMaxBot::max_value(GameState* gamestate, int alpha, int beta){
	//printIndent(gamestate->min_max_depth); std::cerr << "In max_value at depth " << gamestate->min_max_depth << ". Bots: " << max_bots.size() << " timeout: " << timeout << std::endl;
	if(terminal_test(gamestate)){
		gamestate->simulateToArrivalAllFleets();
		return utility_value(gamestate);
	}
	minmax_depth_reached = (minmax_depth_reached<gamestate->min_max_depth) ? gamestate->min_max_depth : minmax_depth_reached;
	int v = -std::numeric_limits<int>::max(), temp_v;
	Successors* successors = stateSuccessors(gamestate, PLAYER_1, max_bots);
	Successor *temp_successor;
	
	for(uint i=0;i<successors->size();i++){
		temp_successor = successors->at(i);
		temp_v = min_value(temp_successor->gamestate, alpha, beta);
		if(temp_v>v) v=temp_v;
		if(v>=beta){
			//std::cerr << "Pruning in max" << std::endl;
			num_alpha_beta_prunes++;
			break;
		}
		if(v>alpha) alpha=v;
	}
	for(uint i=0;i<successors->size();i++){
		temp_successor = successors->at(i);
		//delete temp_successor->gamestate;
		//delete temp_successor->orders;
		delete temp_successor;
	}
	successors->clear();
	delete successors;
	//printIndent(gamestate->min_max_depth);std::cerr << "Run of max_value at depth " << gamestate->min_max_depth << " took " << timer2.MicrosElapsed() << std::endl;
	return v;
}
int MinMaxBot::min_value(GameState* gamestate, int alpha, int beta){
	//printIndent(gamestate->min_max_depth); std::cerr << "In min_value at depth " << gamestate->min_max_depth << ". Bots: " << min_bots.size() << " timeout: " << timeout << " minmax_depth_limit: " << minmax_depth_limit << std::endl;
	if(terminal_test(gamestate)){
		gamestate->simulateToArrivalAllFleets();
		return utility_value(gamestate);
	}
	
	minmax_depth_reached = (minmax_depth_reached<gamestate->min_max_depth) ? gamestate->min_max_depth : minmax_depth_reached;
	int v = std::numeric_limits<int>::max(), temp_v;
	Successors* successors = stateSuccessors(gamestate, PLAYER_2, min_bots);
	Successor *temp_successor;
	
	for(uint i=0;i<successors->size();i++){
		temp_successor = successors->at(i);
		temp_v = max_value(temp_successor->gamestate, alpha, beta);
		if(temp_v<v) v=temp_v;
		if(v<=alpha){
			//std::cerr << "Pruning in min" << std::endl;
			num_alpha_beta_prunes++;
			break;
		}
		if(v<beta) beta = v;
	}
	for(uint i=0;i<successors->size();i++){
		temp_successor = successors->at(i);
		//delete temp_successor->gamestate;
		//delete temp_successor->orders;
		delete temp_successor;
	}
	successors->clear();
	delete successors;
	//printIndent(gamestate->min_max_depth);std::cerr << "Run of min_value at depth " << gamestate->min_max_depth << " took " << timer2.MicrosElapsed() << std::endl;
	return v;
}

int MinMaxBot::utility_value(GameState* gamestate){
	int shipcount_p1 = gamestate->shipCountForPlayerID(PLAYER_1);
	int shipcount_p2 = gamestate->shipCountForPlayerID(PLAYER_2);
	uint growth_rate_p1 = gamestate->growthRateForPlayerID(PLAYER_1);
	uint growth_rate_p2 = gamestate->growthRateForPlayerID(PLAYER_2);
	
	return shipcount_p1-shipcount_p2 + (growth_rate_p1-growth_rate_p2)*(200-gamestate->turn);
}
bool MinMaxBot::terminal_test(GameState* gamestate){
	//std::cerr << "Terminal Test turn " << gamestate->turn << " depth: " << gamestate->min_max_depth << std::endl;
	return gamestate->turn>=200 || gamestate->min_max_depth>=minmax_depth_limit;
}

Successors* MinMaxBot::stateSuccessors(GameState *gamestate, uint playerID, Bots bots){
	Successors* successors = new Successors();
	BaseBot* bot;
	
	for(uint i=0;i<bots.size();i++){
		bot = bots.at(i);
		successors->push_back(runStateForBot(gamestate, bot, playerID));
		num_minmax_nodes++;
	}
	return successors;
}

Successor* MinMaxBot::runStateForBot(GameState* gamestate, BaseBot* bot, uint playerID){
	Successor* successor = new Successor();
	GameState* gs = new GameState(*gamestate);
	Orders* botOrders = bot->doTurn(gs, playerID);
	/*if(gs->min_max_depth==0){
		std::cerr << "running bot as player " << playerID << " Bot would make the orders:" << std::endl;
		for(int i=0;i<botOrders->size();i++){
			Order* order = botOrders->at(i);
			std::cerr << order->source_planet_id << " -> " << order->destination_planet_id << " " << order->shipsCount << std::endl;
		}
	}*/
	if(playerID==PLAYER_1){
		// Turn count gets increased in GameState.advanceGameState()
		// so we should only do so after player 2's turn.
		gs->turn--;
	}
	gs->advanceGameState();
	gs->min_max_depth++;
	successor->gamestate = gs;
	successor->orders = botOrders;
	return successor;
}
