/*
 *  Fleet.cpp
 *  planetwars_cpp1
 *
 *  Created by Barry Hurley on 09/11/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#include <iostream>
#include "Fleet.h"
#include "GameState.h"
#include "point2d.h"
#include "Planet.h"
#include "Player.h"


Fleet::Fleet(const uint ownerID, const uint source_planet_id, const uint destination_planet_id, uint num_ships, uint total_trip_length) :
	_ownerID(ownerID),
	_source_planet_id(source_planet_id),
	_destination_planet_id(destination_planet_id),
	_num_ships(num_ships),
	_total_trip_length(total_trip_length)
	//_total_trip_length(Point::distanceBetween(source_planet->coordinate(), destination_planet->coordinate()))
{
	_turns_remaining = _total_trip_length;
}

Fleet::Fleet(const uint ownerID, const uint source_planet_id, const uint destination_planet_id, uint num_ships, uint total_trip_length, uint turns_remaining) :
	_ownerID(ownerID),
	_source_planet_id(source_planet_id),
	_destination_planet_id(destination_planet_id),
	_num_ships(num_ships),
	_total_trip_length(total_trip_length),
	_turns_remaining(turns_remaining)
{	
}

Fleet::Fleet(const Fleet& f) : 
	_ownerID(f._ownerID),
	_source_planet_id(f._source_planet_id),
	_destination_planet_id(f._destination_planet_id),
	_num_ships(f._num_ships),
	_total_trip_length(f._total_trip_length),
	_turns_remaining(f._turns_remaining)
{
}

Fleet::~Fleet() {
	// TODO Auto-generated destructor stub
}

const uint Fleet::OwnerID() const{
	return _ownerID;
}

const uint Fleet::SourcePlanetID() const{
	return _source_planet_id;
}

const uint Fleet::DestinationPlanetID() const{
	return _destination_planet_id;
}

const uint Fleet::NumShips() const{
	return _num_ships;
}

const uint Fleet::TotalTripLength() const{
	return _total_trip_length;
}

uint Fleet::TurnsRemaining() const{
	return _turns_remaining;
}

void Fleet::DecreaseTurnsRemaining(){
	_turns_remaining--;
}

/* Returns true if f1's turns remaining is less than f2's */
bool Fleet::compareTurnsRemaining(const Fleet* f1, const Fleet* f2){
	return f1->TurnsRemaining() < f2->TurnsRemaining();
}

bool Fleet::operator == (const Fleet& fleet) const{
    return (_ownerID==fleet.OwnerID() &&
		   _source_planet_id==fleet.SourcePlanetID() &&
		   _destination_planet_id==fleet.DestinationPlanetID() &&
		   _num_ships==fleet.NumShips() &&
			_turns_remaining==fleet.TurnsRemaining() );
}

#ifdef DEBUG
std::ostream& operator << (std::ostream& out, const Fleet& f){
	out << "F(" << f._num_ships << ") " << f._source_planet_id << "->" << f._destination_planet_id 
		<< " " << f._turns_remaining << "/" << f._total_trip_length << " turns";
	return out;
}
#endif
