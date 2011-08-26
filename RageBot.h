/*
 *  RageBot.h
 *  planetwars_cpp1
 *
 *  Created by Barry Hurley on 11/11/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef RAGEBOT_H_
#define RAGEBOT_H_

#include "defines.h"
#include "BaseBot.h"

class RageBot : public BaseBot {
	
public:
	Orders* doTurn(GameState* gamestate, uint myPlayerID);
	
private:
};

#endif
