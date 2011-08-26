/*
 *  ReinforcerBot.cpp
 *  planetwars_cpp1
 *
 *  Created by Barry Hurley on 18/11/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ReinforcerBot.h"

#include "Fleet.h"
#include "GameState.h"
#include "order.h"
#include "Planet.h"
#include "Player.h"
#include <iostream>
#include <algorithm>
#include <vector>

Planet* globalPlanet_reinforcerbot;
bool closerToGlobalPlanet_reinforcerbot_wrapper(const Planet* p1, const Planet* p2){
	if(globalPlanet_reinforcerbot){
		return globalPlanet_reinforcerbot->closerPlanetToMe(p1, p2);
	}
	return false;
}

Orders* ReinforcerBot::doTurn(GameState* gamestate, uint myPlayerID){
	Orders* orders = new Orders();
	uint myEnemyID = Player::myEnemy(myPlayerID);
	Planets* myPlanets = gamestate->findPlanets(myPlayerID);
	Fleets* enemyFleets = gamestate->findFleetsByOwner(myEnemyID);
	Planet* targetPlanet;
	Planet* myPlanet;
	Fleet* targetFleet;
	
	sort(enemyFleets->begin(), enemyFleets->end(), &Fleet::compareTurnsRemaining);
	
	for(uint i=0;i<enemyFleets->size();i++){
		targetFleet = enemyFleets->at(i);
		targetPlanet = gamestate->getPlanetByID(targetFleet->DestinationPlanetID());
		// We are not interested here in fleets heading for planets other than ours.
		if(targetPlanet->OwnerID()!=myPlayerID) continue;

		globalPlanet_reinforcerbot = targetPlanet;
		uint fleet_turns_remaining = targetFleet->TurnsRemaining();
		uint predicted_target_planet_ship_count = targetPlanet->simpleShipsCountPrediction(fleet_turns_remaining);
		uint ships_needed = targetFleet->NumShips()-predicted_target_planet_ship_count;
		// If the planet has enough ships to defend itself, then no need to reinforce.
		if(ships_needed<=0) continue;
		
		sort(myPlanets->begin(), myPlanets->end(), closerToGlobalPlanet_reinforcerbot_wrapper);
		
		for(uint j=0;j<myPlanets->size();j++){
			myPlanet = myPlanets->at(j);
			uint ships_available = myPlanet->simpleShipsAvailable(gamestate, myEnemyID);
			if(targetPlanet!=myPlanet && ships_available>=ships_needed){
				//std::cerr << "Reinforcer bot sending " << ships_needed << " to " << targetPlanet->planetID() << std::endl;
				Order* order = new Order(myPlanet->planetID(), targetPlanet->planetID(), ships_needed);
				orders->push_back(order);
				gamestate->issueOrder(order);
				break;
			}
		}
	}
	
	delete myPlanets;
	delete enemyFleets;
	
	return orders;
}
