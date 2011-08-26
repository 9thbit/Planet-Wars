/*
 *  InferBot.h
 *  planetwars_cpp1
 *
 *  Created by Barry Hurley on 17/01/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef INFERBOT_H_
#define INFERBOT_H_

#include "defines.h"

class InferBot {
public:
	InferBot(GameState* gamestate, uint myPlayerID);
	//Orders* doTurn();
    Orders* inferOrders(GameState *gs, uint player);
	
private:
	GameState* _gamestate;
	GameState* _gamestate_prevturn;
	uint _myPlayerID;
	uint _myEnemyID;
};

#endif