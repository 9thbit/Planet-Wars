/*
 *  RageBot.cpp
 *  planetwars_cpp1
 *
 *  Created by Barry Hurley on 11/11/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "RageBot.h"

#include "GameState.h"
#include "order.h"
#include "Planet.h"
#include "Player.h"
#include <iostream>

Orders* RageBot::doTurn(GameState* gamestate, uint myPlayerID){
	Orders* orders = new Orders();
	uint myEnemyID = Player::myEnemy(myPlayerID);
	Planets* myPlanets = gamestate->findPlanets(myPlayerID);
	Planets* enemyPlanets = gamestate->findPlanets(myEnemyID);
	Planet* myPlanet;
	Planet* enemyPlanet;
	Planet* nearestEnemyPlanet;
	
	for(uint i=0;i<myPlanets->size();i++){
		myPlanet = myPlanets->at(i);
		nearestEnemyPlanet = NULL;
		uint closestDistance = 999999;
		uint thisDistance;
		uint ships_available = myPlanet->simpleShipsAvailable(gamestate, myEnemyID);
		
		for(uint j=0;j<enemyPlanets->size();j++){
			enemyPlanet = enemyPlanets->at(j);
			thisDistance = gamestate->turnDistanceBetweenPlanets(myPlanet, enemyPlanet);
			
			if(!nearestEnemyPlanet || thisDistance<closestDistance){
				nearestEnemyPlanet = enemyPlanet;
				closestDistance = thisDistance;
			}
		}
		
		if(nearestEnemyPlanet && ships_available>0){
			Order *order = new Order(myPlanet->planetID(), enemyPlanet->planetID(), ships_available);
			orders->push_back(order);
			gamestate->issueOrder(order);
		}
	}
	
	delete myPlanets;
	delete enemyPlanets;
	
	return orders;
}
