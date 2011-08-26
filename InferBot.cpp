/*
 *  InferBot.cpp
 *  planetwars_cpp1
 *
 *  Created by Barry Hurley on 17/01/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "InferBot.h"
#include "order.h"
#include "Fleet.h"
#include "Planet.h"
#include "Player.h"
#include "GameState.h"
#include <iostream>

InferBot::InferBot(GameState* gamestate, uint myPlayerID) :
	_gamestate(gamestate),
	_myPlayerID(myPlayerID)
{
	_myEnemyID = Player::myEnemy(_myPlayerID);
	_gamestate_prevturn = NULL;
}

/*Orders* InferBot::doTurn(){
	std::cerr << "a" << std::endl;
	Orders* orders = NULL;
	if(_gamestate->turn>1){
		orders = inferOrders(_gamestate_prevturn, _gamestate, _myEnemyID);
	} else {
		// Can't infer orders on first turn.
		orders = new Orders();
	}
	
	// Copy and save the current gamestate. Delete old one if necessary.
	if(_gamestate_prevturn!=NULL) delete _gamestate_prevturn;
	_gamestate_prevturn = new GameState(*_gamestate);
	
	return orders;
}*/

Orders* InferBot::inferOrders(GameState *gs, uint player){
    Orders *orders = new Orders();
    /*Planets *planets_before = gs_before->planets();
    Planets *planets_after = gs_after->planets();
    for(int i=0;i<planets_before->size();i++){
        Planet *p_before = planets_before->at(i);
        Planet *p_after = planets_after->at(i);
        
        if(*p_before!=*p_after){
			std::cerr << "Found planet that changed: " << p_before->planetID() << std::endl;
        }
    }*/
	
	// We look at all 'player's fleets and note any that were just sent.
	// What about fleets that have a distance of 1 to travel? Minimum distance between planets is 2:
	// http://ai-contest.com/forum/viewtopic.php?f=3&t=1094&p=7224&hilit=minimum#p7224
	Fleets *fleets_after = gs->fleets();
	for(uint i=0;i<fleets_after->size();i++){
		Fleet *f = fleets_after->at(i);
		if(f->OwnerID()==player && f->TurnsRemaining()==f->TotalTripLength()-1){
#ifdef DEBUG
			std::cerr << "New enemy fleet detected "  << *f << std::endl;
#endif
			std::cerr << "Enemy made the move: " << f->SourcePlanetID() << " "
				<< f->DestinationPlanetID() << " " << f->NumShips() << std::endl;
			orders->push_back(new Order(f->SourcePlanetID(), f->DestinationPlanetID(), f->NumShips()));
		}
	}
	
    return orders;
}
