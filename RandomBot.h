/*
 *  RandomBot.h
 *  planetwars_cpp1
 *
 *  Created by Barry Hurley on 12/11/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef RANDOMBOT_H_
#define RANDOMBOT_H_

#include "defines.h"
#include "BaseBot.h"

class RandomBot : public BaseBot {
	
public:
	Orders* doTurn(GameState* gamestate, uint myPlayerID);
	
private:
};

#endif
