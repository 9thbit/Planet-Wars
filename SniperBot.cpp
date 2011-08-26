/*
 *  SniperBot.cpp
 *  planetwars_cpp1
 *
 *  Created by Barry Hurley on 13/11/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "SniperBot.h"

#include "Fleet.h"
#include "GameState.h"
#include "order.h"
#include "Planet.h"
#include "Player.h"
#include <iostream>
#include <algorithm>
#include <vector>

Planet* globalPlanet_sniperbot;
bool closerToGlobalPlanet_sniperbot_wrapper(const Planet* p1, const Planet* p2){
	if(globalPlanet_sniperbot){
		return globalPlanet_sniperbot->closerPlanetToMe(p1, p2);
	}
	return false;
}

Orders* SniperBot::doTurn(GameState* gamestate, uint myPlayerID){
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
		//targetPlanet = (Planet*)targetFleet->DestinationPlanet();
		targetPlanet = gamestate->getPlanetByID(targetFleet->DestinationPlanetID());
		globalPlanet_sniperbot = targetPlanet;
		uint fleet_turns_remaining = targetFleet->TurnsRemaining();
		
		sort(myPlanets->begin(), myPlanets->end(), closerToGlobalPlanet_sniperbot_wrapper);
		
		for(uint j=0;j<myPlanets->size();j++){
			myPlanet = myPlanets->at(j);
			uint dist_to_target_planet = Point::distanceBetween(targetPlanet->coordinate(), myPlanet->coordinate());
			uint ships_to_send = targetPlanet->simpleShipsCountPrediction(dist_to_target_planet+1) + targetFleet->NumShips();
			if(dist_to_target_planet>fleet_turns_remaining+1){
				//std::cerr << "No planets close enough to attack Fleet targeting p " << targetPlanet->planetID() << std::endl;
				break;
			}
			uint ships_available = myPlanet->simpleShipsAvailable(gamestate, myEnemyID);
			if(dist_to_target_planet==fleet_turns_remaining+1 && ships_available>=ships_to_send){ //FIXME ship count
				Order* order = new Order(myPlanet->planetID(), targetPlanet->planetID(), ships_to_send);
				orders->push_back(order);
				gamestate->issueOrder(order);
				break;
			} else if(dist_to_target_planet<=fleet_turns_remaining && ships_available>=ships_to_send){
				// 
				break;
			}
		}
	}
	
	delete myPlanets;
	delete enemyFleets;
	
	return orders;
}
