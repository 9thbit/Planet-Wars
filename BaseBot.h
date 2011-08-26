/*
 *  BaseBot.h
 *  planetwars_cpp1
 *
 *  Created by Barry Hurley on 15/11/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef BASEBOT_H_
#define BASEBOT_H_

#include "defines.h"

class BaseBot {
public:
	virtual Orders* doTurn(GameState*, uint) = 0;
};

#endif
