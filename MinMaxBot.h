/*
 *  MinMaxBot.h
 *  planetwars_cpp1
 *
 *  Created by Barry Hurley on 10/11/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef MINMAXBOT_H_
#define MINMAXBOT_H_

#include "defines.h"

class MinMaxBot {
	
public:
	MinMaxBot(GameState* gamestate, uint myPlayerID);
	~MinMaxBot();
	Orders* doTurn();
	
private:
	Orders* minimax_decision(GameState *gamestate);
	Orders* alphabeta_decision(GameState *gamestate);
	Successors* stateSuccessors(GameState *gamestate, uint playerID, Bots bots);
	Successor* runStateForBot(GameState* gamestate, BaseBot* bot, uint playerID);
	void SavePotentialEnemyOrdersForNextTurn();
	void compareBotOrders(Orders *enemyOrders);
	bool compareOrders(Orders* orders1, Orders* orders2);
	bool tiebreakUpdateMaxSuccessor(Successor *max_successor, Successor *candidate);
	
	int min_value(GameState* gamestate);
	int max_value(GameState* gamestate);
	int min_value(GameState* gamestate, int alpha, int beta);
	int max_value(GameState* gamestate, int alpha, int beta);
	int utility_value(GameState* gamestate);
	bool terminal_test(GameState* gamestate);
	uint calculateMinMaxDepthLimit(long long microseconds);
	
	GameState *_gamestate, *previous_turn_gamestate;
	Bots _bots, max_bots, min_bots;
	CaseBasedBot *caseBasedBot;
	InferBot *inferBot;
	uint _myPlayerID;
	uint _myEnemyID;
	uint minmax_depth_limit;
	uint minmax_depth_reached;
	Successors* potentialEnemyTurnSuccessors;
	Timer *branchTimer;
	Stats *nodesms_stats;
	double bot_turn_timeout;
};

#endif
