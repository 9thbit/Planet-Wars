/*
 *  GameState.h
 *  planetwars_cpp1
 *
 *  Created by Barry Hurley on 09/11/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "defines.h"
#include "point2d.h"

class GameState {
public:
	GameState();
	GameState(const GameState& gs);
	~GameState();
	void updatePlanet(uint planetID, uint shipsCount, uint growthRate, Point coordinate, uint ownerID);
	void updateFleet(uint sourcePlanetID, uint destPlanetID, uint shipsCount, uint tripLength, uint turnsRemaining, uint ownerID);
	void advanceGameState();
	void simulateToArrivalAllFleets();
	void issueOrder(Order *order);
	double compareTo(GameState *gs2);
	Planets* planets();
	Planets* findPlanets(uint ownerID);
	Planets* findOthersPlanets(uint notOwnerID);
	Planet* getPlanetByID(uint planetID);
	Fleets* fleets();
	Fleets* findFleetsByOwner(uint ownerID);
	Fleets* findFleetsByDestinationPlanet(uint planetID);
	Fleets* findFleetsByOwnerAndDestinationPlanet(uint ownerID, uint planetID);
	uint shipCountForPlayerID(uint playerID);
	uint growthRateForPlayerID(uint playerID);
	uint turnDistanceBetweenPlanets(Planet* p1, Planet* p2);
	uint turn, min_max_depth, player_to_move;
	
	//sourcePlanet, destinationPlanet, shipsCount, tripLength, turnsRemaining
private:
	Planets _planets;
	Fleets _fleets;
};

#endif
