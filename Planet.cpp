/*
 *  Planet.cpp
 *  planetwars_cpp1
 *
 *  Created by Barry Hurley on 09/11/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Planet.h"
#include "Fleet.h"
#include "GameState.h"
#include "Player.h"
#include "point2d.h"
#include <iostream>

Planet::Planet(uint planetID, uint shipsCount, uint growthRate, Point coordinate, const uint ownerID) :
	ships_count(shipsCount),
	_planet_id(planetID),
	_growth_rate(growthRate),
	_coordinate(coordinate),
	_ownerID(ownerID)
{
}

Planet::Planet(const Planet& p) :
	ships_count(p.ships_count),
	_planet_id(p._planet_id),
	_growth_rate(p._growth_rate),
	_coordinate(p.coordinate()),
	_ownerID(p._ownerID)
{	
}

void Planet::updateDetails(uint new_ships_count, uint growth_rate, const uint ownerID){
	ships_count = new_ships_count;
	_growth_rate = growth_rate;
	_ownerID = ownerID;
}

/*void Planet::setShipsCount(uint new_ships_count){
	_ships_count = new_ships_count;
}*/

const uint Planet::planetID() const{
	return _planet_id;
}

/*uint Planet::shipsCount() const{
	return _ships_count;
}*/

uint Planet::growthRate() const{
	return _growth_rate;
}

Point Planet::coordinate() const{
	return _coordinate;
}

const uint Planet::OwnerID() const{
	return _ownerID;
}

uint Planet::simpleShipsCountPrediction(uint nr_turns) const{
	uint est_ships_count = ships_count;
	if(_ownerID!=PLAYER_NEUTRAL){
		est_ships_count+=_growth_rate*nr_turns;
	}
	return est_ships_count;
}

uint Planet::simpleShipsAvailable(GameState* gamestate, uint myEnemyID){
	Fleets* arrivingFleets = gamestate->findFleetsByOwnerAndDestinationPlanet(myEnemyID, _planet_id); //FIXME need to add back my arriving ships.
	uint enemy_ships_arriving = 0;
	for(uint i=0;i<arrivingFleets->size();i++)enemy_ships_arriving+=(arrivingFleets->at(i)->NumShips());
	delete arrivingFleets;
	return enemy_ships_arriving>ships_count ? 0 : ships_count - enemy_ships_arriving;
}

void Planet::advanceState(uint nr_turns, Fleets* arrivingFleets){
	Fleet* tempFleet;
	for(uint i=1;i<=nr_turns;i++){
		uint ships[NUM_PLAYERS];
		ships[PLAYER_NEUTRAL]=ships[PLAYER_1]=ships[PLAYER_2]=0;
		
		if(_ownerID!=PLAYER_NEUTRAL){
			ships_count+=_growth_rate;
		}
		ships[_ownerID]=ships_count;
		
		for(uint j=0;j<arrivingFleets->size();j++){
			tempFleet = arrivingFleets->at(j);
			if(tempFleet->TurnsRemaining()==i){
				ships[tempFleet->OwnerID()]+=tempFleet->NumShips();
			}
		}
		
		//std::cerr << "arriving ships: " << ships[0] << " " << ships[1] << " " << ships[2] << std::endl;
		uint greatest_id = _ownerID;
		uint second_greatest_id=0;
		for(uint j=0;j<NUM_PLAYERS;j++){
			if(ships[j]>ships[greatest_id]) greatest_id=j;
		}
		for(uint j=0;j<NUM_PLAYERS;j++){
			if(j!=greatest_id && ships[j]>ships[second_greatest_id]) second_greatest_id=j;
		}
		
		//std::cerr << "Player " << greatest_id << " has ships: " << ships[greatest_id] << " second: " << second_greatest_id << " " << ships[second_greatest_id] << std::endl;
		
		if(ships[greatest_id]==ships[second_greatest_id]){
			ships_count = 0;
		} else {
			//std::cerr << "setting owner: " << greatest_id << " new ship count: " << ships[greatest_id]-ships[second_greatest_id] << std::endl;
			_ownerID = greatest_id;
			ships_count = ships[greatest_id]-ships[second_greatest_id];
		}
	}
}

double Planet::compareTo(const Planet *p2) const {
	uint ships_count_diff = ships_count - p2->ships_count; 
	uint growth_rate_diff = _growth_rate - p2->_growth_rate; 
	uint ownerID_diff = _ownerID - p2->_ownerID;
	uint coordinate_diff = Point::distanceBetween(_coordinate, p2->_coordinate);
	
	// ^2 the differences
	ships_count_diff*=ships_count_diff; 
	growth_rate_diff*=growth_rate_diff;
	ownerID_diff*=ownerID_diff;
	//coordinate_diff*=coordinate_diff;
	
	return 0; //FIXME
}


/* Returns true if p1 is closer to this planet than p2 */
bool Planet::closerPlanetToMe(const Planet* p1, const Planet* p2){
	//FIXME cache distances
	uint p1_dist = Point::distanceBetween(_coordinate, p1->coordinate());
	uint p2_dist = Point::distanceBetween(_coordinate, p2->coordinate());
	return p1_dist < p2_dist;
}

bool Planet::compareShipsCount(const Planet* p1, const Planet* p2) {
	return p1->ships_count < p2->ships_count;
}

bool Planet::operator == (const Planet& p2) const{
    return (_planet_id==p2._planet_id && _ownerID==p2._ownerID && ships_count==p2.ships_count);
}

bool Planet::operator != (const Planet& p2) const{
    return !(*this==p2);
}

