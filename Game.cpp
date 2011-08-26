/*
 *  Game.cpp
 *  planetwars_cpp1
 *
 *  Created by Barry Hurley on 09/11/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#include <iostream>
#include "Game.h"
#include "GameState.h"
#include "order.h"
#include "Player.h"
#include "Planet.h"
#include "StringTokenizer.h"

Game::Game():
	_turn(0),
	_current_planet_id(0),
	_current_fleet_id(0)
{
	_gamestate = new GameState();
	_gamestate->player_to_move = PLAYER_1;
}

Game::~Game(){
	delete _gamestate;
}

void Game::updateState(const std::string& stateLine){
	std::vector<std::string> tokens = StringTokenizer::split(stateLine, ' ');
	uint tokensSize = tokens.size();
	//Ignore blank lines
	if (tokensSize>1) {
		std::string firstToken = tokens.at(0);
		if(firstToken=="P" && tokensSize==6){
			//std::cout << "Planet " << _current_planet_id << std::endl;
			Point coordinate = Point(atof(tokens.at(1).c_str()), atof(tokens.at(2).c_str()));
			uint ownerID	 = atoi(tokens.at(3).c_str());
			uint shipsCount  = atoi(tokens.at(4).c_str());
			uint growthRate  = atoi(tokens.at(5).c_str());
			
			_gamestate->updatePlanet(_current_planet_id++, shipsCount, growthRate, coordinate, ownerID);
		} else if (firstToken=="F" && tokensSize==7) {
			//std::cerr << "Fleet " << _current_fleet_id++ << std::endl;
			uint ownerID        = atoi(tokens.at(1).c_str());
            uint shipsCount     = atoi(tokens.at(2).c_str());
			uint sourcePlanetID = atoi(tokens.at(3).c_str());
			uint destPlanetID	= atoi(tokens.at(4).c_str());
            uint tripLength     = atoi(tokens.at(5).c_str());
            uint turnsRemaining = atoi(tokens.at(6).c_str());
			
			_gamestate->updateFleet(sourcePlanetID, destPlanetID, shipsCount, tripLength, turnsRemaining, ownerID);
		}
	}
}

void Game::issueOrders(Orders* orders){
	Order* order;
	for(uint i=0;i<orders->size();i++){
		order = orders->at(i);
		std::cout << order->source_planet_id << " " << order->destination_planet_id << " " << order->shipsCount << std::endl;
	}
}

void Game::finishTurn(){
	_current_planet_id = _current_fleet_id = 0;
	
	//FIXME: move this to a turn_done method or something
	std::cout << "go" << std::endl;
	std::cout.flush();
	_gamestate->advanceGameState();
}

GameState* Game::gameState(){
	return _gamestate;
}
