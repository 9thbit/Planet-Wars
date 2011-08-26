/*
 *  Simple1Bot.h
 *  planetwars_cpp1
 *
 *  Created by Barry Hurley on 12/11/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef SIMPLE1BOT_H_
#define SIMPLE1BOT_H_

#include "defines.h"
#include "BaseBot.h"

class Simple1Bot : public BaseBot {
	
public:
	Orders* doTurn(GameState* gamestate, uint myPlayerID);
	
private:
};

#endif
