//
//  CaseBasedBot.h
//  planetwars_cpp1
//
//  Created by Barry Hurley on 08/03/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef CASEBASEDBOT_H_
#define CASEBASEDBOT_H_

#include "defines.h"
#include "BaseBot.h"

class CaseBasedBot : public BaseBot {
public:
	CaseBasedBot();
	~CaseBasedBot();
	Orders *doTurn(GameState *gamestate, uint myPlayerID);
	void addEnemyMove(GameState *gamestate, Orders *orders);
	
private:
	Successors *enemyMoves;
	void compareToPreviousGameStates(GameState *gamestate);
};

#endif