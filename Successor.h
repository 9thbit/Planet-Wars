/*
 *  Successor.h
 *  planetwars_cpp1
 *
 *  Created by Barry Hurley on 17/11/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef SUCCESSOR_H_
#define SUCCESSOR_H_

#include "defines.h"

class Successor {
#ifdef DEBUG
	friend std::ostream& operator<<(std::ostream& out, const Successor& s);
#endif
public:
	~Successor();
	GameState *gamestate;
	Orders* orders;
};

#endif
