/*
 *  Simple1Bot.cpp
 *  planetwars_cpp1
 *
 *  Created by Barry Hurley on 12/11/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Simple1Bot.h"

#include "GameState.h"
#include "order.h"
#include "Planet.h"
#include "Player.h"
#include <iostream>
#include <algorithm>
#include <vector>

Planet* globalPlanet_simple1bot;
bool closerToGlobalPlanet_simple1bot_wrapper(const Planet* p1, const Planet* p2){
	if(globalPlanet_simple1bot){
		return globalPlanet_simple1bot->closerPlanetToMe(p1, p2);
	}
	return false;
}

Orders* Simple1Bot::doTurn(GameState* gamestate, uint myPlayerID){
	Orders* orders = new Orders();
	uint myEnemyID = Player::myEnemy(myPlayerID);
	Planets* myPlanets = gamestate->findPlanets(myPlayerID);
	Planets* otherPlanets = gamestate->findOthersPlanets(myPlayerID);
	Planet* myPlanet;
	Planet* targetPlanet;
	//Planet* nearestEnemyPlanet;
	
	//std::cerr << "Sorting enemy planets." << std::endl;
	
	// Sort the list of other planets by ship count
	sort(otherPlanets->begin(), otherPlanets->end(), &Planet::compareShipsCount);
	
	for(uint i=0;i<otherPlanets->size();i++){
		targetPlanet = globalPlanet_simple1bot = otherPlanets->at(i);
		//std::cerr << "Target Planet " << targetPlanet->planetID() << " ships: " << targetPlanet->ships_count << std::endl;
		
		sort(myPlanets->begin(), myPlanets->end(), closerToGlobalPlanet_simple1bot_wrapper);
		for (uint j=0; j<myPlanets->size(); j++) {
			myPlanet = myPlanets->at(j);
			uint turn_dist_to_target = Point::distanceBetween(targetPlanet->coordinate(), myPlanet->coordinate());
			uint ships_needed = targetPlanet->simpleShipsCountPrediction(turn_dist_to_target)+1;
			uint ships_available = myPlanet->simpleShipsAvailable(gamestate, myEnemyID);
			
			if(ships_available>=ships_needed){
				//std::cerr << "Sending " << ships_needed << " ships from " << myPlanet->planetID() << " to " << targetPlanet->planetID() << std::endl;
				Order* order = new Order(myPlanet->planetID(), targetPlanet->planetID(), ships_needed);
				orders->push_back(order);
				gamestate->issueOrder(order);
				break;
			}
		}
	}
	//std::cerr << "F" << std::endl;
	
	delete myPlanets;
	delete otherPlanets;

	return orders;
}
