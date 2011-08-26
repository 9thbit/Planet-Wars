//
//  CaseBasedBot.cpp
//  planetwars_cpp1
//
//  Created by Barry Hurley on 08/03/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "CaseBasedBot.h"

#include "GameState.h"
#include "Successor.h"
#include <vector>
#include <iostream>

CaseBasedBot::CaseBasedBot(){
	enemyMoves = new Successors(); 
}

CaseBasedBot::~CaseBasedBot(){
	/* FIXME
	for(uint i=0;i<enemyMoves->size();i++){
		delete enemyMoves->at(i);
	}*/
	delete enemyMoves;
}


Orders *CaseBasedBot::doTurn(GameState *gamestate, uint myPlayerID){
	Orders *orders = new Orders();
	return orders;
}

void CaseBasedBot::addEnemyMove(GameState *gamestate, Orders *orders){
	// check if the gamestate is within the previously seen ones
	
	compareToPreviousGameStates(gamestate);
	/*Successor *s = new Successor();
	s->gamestate = gamestate;
	s->orders = orders;
	enemyMoves->push_back(s);*/
}

void CaseBasedBot::compareToPreviousGameStates(GameState *gamestate){
	Successor *s;
	GameState *gs;
	for(std::vector<Successor*>::iterator s_it = enemyMoves->begin();s_it!=enemyMoves->end();s_it++){
		s = *s_it;
		gs = s->gamestate;
		std::cerr << "Comparing gamestates at " << gamestate << " and " << gs << std::endl;
		double similarity = gamestate->compareTo(gs);
		std::cerr << "Gamestate similarity: " << similarity << std::endl;
	}
}