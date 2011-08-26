/*
 *  ReinforcerBot.h
 *  planetwars_cpp1
 *
 *  Created by Barry Hurley on 18/11/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef REINFORCERBOT_H_
#define REINFORCERBOT_H_

#include "defines.h"
#include "BaseBot.h"

class ReinforcerBot : public BaseBot{
	
public:
	Orders* doTurn(GameState* gamestate, uint myPlayerID);
	
private:
};

#endif
