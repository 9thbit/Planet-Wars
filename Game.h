/*
 *  Game.h
 *  planetwars_cpp1
 *
 *  Created by Barry Hurley on 09/11/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef GAME_H_
#define GAME_H_

#include "defines.h"

class Game {
public:
	Game();
	~Game();
	void updateState(const std::string& stateLine);
	void finishTurn();
	GameState* gameState();
	void issueOrders(Orders* orders);
	
private:
	uint _turn, _current_planet_id, _current_fleet_id;
	GameState* _gamestate;
};

#endif
