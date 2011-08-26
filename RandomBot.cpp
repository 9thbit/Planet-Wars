/*
 *  RandomBot.cpp
 *  planetwars_cpp1
 *
 *  Created by Barry Hurley on 12/11/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "RandomBot.h"

#include "GameState.h"
#include "order.h"
#include "Planet.h"
#include "Player.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Orders* RandomBot::doTurn(GameState* gamestate, uint myPlayerID){
	Orders* orders = new Orders();
	//uint myEnemyID = Player::myEnemy(myPlayerID);
	Planets* myPlanets = gamestate->findPlanets(myPlayerID);
	Planets* otherPlanets = gamestate->findOthersPlanets(myPlayerID);
	Planet* myPlanet;
	Planet* planetToAttack;
	srand(time(NULL));
	
	/*First check if there are planets to attack and that I own at least one planet */
	if(myPlanets->size()>0 && otherPlanets->size()){
		/* Pick one of my planets and one other planet (not owned by me) */
		myPlanet = myPlanets->at(rand()%myPlanets->size());
		planetToAttack = otherPlanets->at(rand()%otherPlanets->size());
		
		/* Send half the ships from my planet to the other planet */
		if(planetToAttack && myPlanet && myPlanet->ships_count>0){
			Order *order = new Order(myPlanet->planetID(), planetToAttack->planetID(), myPlanet->ships_count/2);
			orders->push_back(order);
			gamestate->issueOrder(order);
		}
	}
	
	delete myPlanets;
	delete otherPlanets;
	
	return orders;
}
