/*
 *  SniperBot.h
 *  planetwars_cpp1
 *
 *  Created by Barry Hurley on 13/11/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef SNIPERBOT_H_
#define SNIPERBOT_H_

#include "defines.h"
#include "BaseBot.h"

class SniperBot : public BaseBot{
	
public:
	Orders* doTurn(GameState* gamestate, uint myPlayerID);
	
private:
};

#endif
