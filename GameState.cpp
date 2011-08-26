/*
 *  GameState.cpp
 *  planetwars_cpp1
 *
 *  Created by Barry Hurley on 09/11/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "GameState.h"
#include "order.h"
#include "point2d.h"
#include "Planet.h"
#include "Player.h"
#include "Fleet.h"
#include "Timer.h"
#include <iostream>
#include <cstdio>

const uint MAX_PLANETS = 100;

int cache_turnDistanceBetweenPlanets[MAX_PLANETS][MAX_PLANETS];

GameState::GameState(){
	turn=1;
	min_max_depth=0;
	for(uint i=0;i<MAX_PLANETS;i++)for(uint j=0;j<MAX_PLANETS;j++)cache_turnDistanceBetweenPlanets[i][j]=-1;
}

GameState::GameState(const GameState& gs){
	const Planets* planets_to_copy = &gs._planets;
	const Fleets* fleets_to_copy = &gs._fleets;
	Planet* p;
	Fleet* f;
	//fprintf(stderr, "Copying GameState at %p\n_planets size: %u", this, (uint)_planets.size());
	turn = gs.turn;
	min_max_depth = gs.min_max_depth;
	
	//Easy to copy planets, fleets a little different because of its references to planets
	for(uint i=0;i<planets_to_copy->size();i++){
		p = planets_to_copy->at(i);
		//std::cerr << "Copying planet at index " << i << " " << p->planetID() << std::endl;
		Planet* p_new = new Planet(*p);
		//fprintf(stderr, "Copied planet at %p to new planet %p\n", p, p_new);
		_planets.push_back(p_new);
	}
	
	for(uint i=0;i<fleets_to_copy->size();i++){
		f = fleets_to_copy->at(i);
		Fleet* f_new = new Fleet(*f);
		//fprintf(stderr, "Copied fleet at %p to new fleet %p\n", f, f_new);
		_fleets.push_back(f_new);
	}
}

GameState::~GameState(){
	//std::cerr << "in GameState destructor" << std::endl;
	for(uint i=0;i<_planets.size();i++){
		delete _planets.at(i);
	}
	for(uint i=0;i<_fleets.size();i++){
		delete _fleets.at(i);
	}
	_planets.clear();
	_fleets.clear();
}

void GameState::updatePlanet(uint planetID, uint shipsCount, uint growthRate, Point coordinate, uint ownerID){
	Planet* p;
	if(planetID>=_planets.size()){
		//new planet
		//std::cout << "Creating new planet " << planetID << std::endl;
		p = new Planet(planetID, shipsCount, growthRate, coordinate, ownerID); //FIXME leak?
		_planets.push_back(p);
	} else {
		p = _planets.at(planetID);
		//std::cout << "Updating planet details " << planetID << std::endl;
		p->updateDetails(shipsCount, growthRate, ownerID);
	}
}

void GameState::updateFleet(uint sourcePlanetID, uint destPlanetID, uint shipsCount, uint tripLength, uint turnsRemaining, uint ownerID){
	//std::cerr << "updateFleet " << sourcePlanetID << " " << destPlanetID << " " << shipsCount << tripLength << std::endl;
	Fleet* f = new Fleet(ownerID, sourcePlanetID, destPlanetID, shipsCount, tripLength, turnsRemaining);
	Fleet* f_temp;
	
	//FIXME, need to improve
	bool fleet_found = false;
	for(uint i=0;i<_fleets.size();i++){
		f_temp = _fleets.at(i);
		if(*f==*f_temp){
			//std::cout << "Matching fleet found" << std::endl;
			fleet_found = true;
			delete f;
			break;
		}
	}
	if(!fleet_found){
		//std::cout << "No matching fleet. adding new." << std::endl;
		_fleets.push_back(f);
	}
}

uint GameState::turnDistanceBetweenPlanets(Planet* p1, Planet* p2){
	if(cache_turnDistanceBetweenPlanets[p1->planetID()][p2->planetID()]<0){
		cache_turnDistanceBetweenPlanets[p1->planetID()][p2->planetID()] = Point::distanceBetween(p1->coordinate(), p2->coordinate());
	}
	return cache_turnDistanceBetweenPlanets[p1->planetID()][p2->planetID()];
}

Planets* GameState::planets(){
	return &_planets;
}

Planets* GameState::findPlanets(uint ownerID){
	Planets* planets = new Planets();
	Planet* p;
	for(uint i=0;i<_planets.size();i++){
		p = _planets.at(i);
		if(p->OwnerID()==ownerID){
			//std::cout << "Found matching owner." << std::endl;
			planets->push_back(p);
		} else {
			//std::cout << "Not matching owner." << std::endl;
		}
	}
	return planets;
}

Planets* GameState::findOthersPlanets(uint notOwnerID){
	Planets* planets = new Planets();
	Planet* p;
	for(uint i=0;i<_planets.size();i++){
		p = _planets.at(i);
		if(p->OwnerID()!=notOwnerID){
			//std::cout << "Found matching owner." << std::endl;
			planets->push_back(p);
		} else {
			//std::cout << "Not matching owner." << std::endl;
		}
	}
	return planets;
}

Planet* GameState::getPlanetByID(uint planetID){
	/*Planet* p = NULL;
	Planet* temp;
	// FIXME do we really need to do this? maybe can just do _planets.at(planetID);
	for(int i=0;i<_planets.size();i++){
		temp = _planets.at(i);
		if(temp->planetID()==planetID){
			p = temp;
			break;
		}
	}
	return p;*/
	return _planets.at(planetID);
}

Fleets* GameState::fleets(){
	return &_fleets;
}

Fleets* GameState::findFleetsByOwner(uint ownerID){
	Fleets* fleets = new Fleets();
	Fleet* f;
	for(uint i=0;i<_fleets.size();i++){
		f = _fleets.at(i);
		if(f->OwnerID()==ownerID){
			fleets->push_back(f);
		}
	}
	return fleets;
}

Fleets* GameState::findFleetsByDestinationPlanet(uint planetID){
	Fleets* fleets = new Fleets();
	Fleet* f;
	for(uint i=0;i<_fleets.size();i++){
		f = _fleets.at(i);
		if(f->DestinationPlanetID()==planetID){
			fleets->push_back(f);
		}
	}
	return fleets;
}

Fleets* GameState::findFleetsByOwnerAndDestinationPlanet(uint ownerID, uint planetID){
	Fleets* fleets = new Fleets();
	Fleet* f;
	for(uint i=0;i<_fleets.size();i++){
		f = _fleets.at(i);
		if(f->OwnerID()==ownerID && f->DestinationPlanetID()==planetID){
			fleets->push_back(f);
		}
	}
	return fleets;
}

uint GameState::shipCountForPlayerID(uint playerID){
	uint ship_count = 0;
	Planet* p;
	for(uint i=0;i<_planets.size();i++){
		p = _planets.at(i);
		if (p->OwnerID()==playerID) {
			ship_count+=p->ships_count;
		}
	}
	Fleet *f;
	for(uint i=0;i<_fleets.size();i++){
		f = _fleets.at(i);
		if(f->OwnerID()==playerID /*&& f->TotalTripLength()!=f->TurnsRemaining()*/){
			ship_count+=f->NumShips();
		}
	}
	return ship_count;
}

uint GameState::growthRateForPlayerID(uint playerID){
	uint growth_rate = 0;
	Planet* p;
	for(uint i=0;i<_planets.size();i++){
		p = _planets.at(i);
		if (p->OwnerID()==playerID) {
			growth_rate+=p->growthRate();
		}
	}
	return growth_rate;
}

void GameState::issueOrder(Order *order){
	// Decrement the number of planets available at the source
	Planet* p = getPlanetByID(order->source_planet_id);
	Planet* p_dest = getPlanetByID(order->destination_planet_id);
	p->ships_count -= order->shipsCount;
	//std::cerr << "Decremeneted P " << p->planetID() << " ship count to " << p->ships_count << std::endl;
	
	// Add the fleet to the fleets array
	Fleet* f = new Fleet(p->OwnerID(), order->source_planet_id, order->destination_planet_id, order->shipsCount, Point::distanceBetween(p->coordinate(), p_dest->coordinate()));
	_fleets.push_back(f);
}

void GameState::advanceGameState(){
	Fleets* fleets_temp;
	Fleet *f;
	Planet *p;
	for(uint i=0;i<_planets.size();i++){
		p = _planets[i];
		fleets_temp = findFleetsByDestinationPlanet(p->planetID());
		p->advanceState(1, fleets_temp);
		delete fleets_temp;
	}
	
	for(uint i=0;i<_fleets.size();i++){
		f = _fleets[i];
		
		f->DecreaseTurnsRemaining();
		//std::cout << "Decreasing turns remaining of fleet to " << f->TurnsRemaining() <<  std::endl;
		if(f->TurnsRemaining()==0){
			//std::cout << "Removing fleet at index " << i << std::endl;
			_fleets.erase(_fleets.begin()+i);
			i--;
		}
	}
	turn++;
}


void GameState::simulateToArrivalAllFleets(){
	//Timer t;
	int turns_simulated=0;
	//t.SetTimeOut(1.0);
	while(_fleets.size()>0 || min_max_depth+turns_simulated<20 ){  //turns_simulated<15
		advanceGameState();
		turns_simulated++;
	}
#ifdef DEBUG
	//std::cerr << "At turn " << turn << " depth: " << min_max_depth << " Turns simulated: " << turns_simulated << " us: " << t.MicrosElapsed() << std::endl;
#endif
}

double GameState::compareTo(GameState *gs2){
	// For now assume it is always the same map
	// Euclidean distance of all metrics
	Planet *p1, *p2;
	uint nr_planets1, nr_planets2;
	
	nr_planets1 = _planets.size(); nr_planets2=gs2->planets()->size();
	
	for(uint i=0;i<nr_planets1 && i<nr_planets2;i++){
		// For now, assuming both gamestates have the the matching planets in the same position
		p1 = _planets.at(i);
		p2 = gs2->planets()->at(i);
		
	}

}
