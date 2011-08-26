/*
 *  Player.h
 *  planetwars_cpp1
 *
 *  Created by Barry Hurley on 09/11/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "defines.h"

class Player{
public:
	static uint myEnemy(uint playerID){
		return  (playerID % 2) + 1;
	}
};

#endif
