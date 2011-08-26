/*
 *  fleet.h
 *  planetwars_cpp1
 *
 *  Created by Barry Hurley on 09/11/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef FLEET_H_
#define FLEET_H_

#include "defines.h"


class Fleet {
#ifdef DEBUG
	friend std::ostream& operator<<(std::ostream& out, const Fleet& f);
#endif
public:
	Fleet(const uint ownerID, const uint source_planet_id, const uint destination_planet_id, uint num_ships, uint total_trip_length);
	Fleet(const uint ownerID, const uint source_planet_id, const uint destination_planet_id, uint num_ships, uint total_trip_length, uint turns_remaining);
	Fleet(const Fleet& f);
	virtual ~Fleet();
	const uint OwnerID() const;
	const uint SourcePlanetID() const;
	const uint DestinationPlanetID() const;
	const uint NumShips() const;
	const uint TotalTripLength() const;
	uint TurnsRemaining() const;
	void DecreaseTurnsRemaining();
	//FIXME: static uint fleetUniqueID(uint sourcePlanetID, uint destPlanetID, uint s
	static bool compareTurnsRemaining(const Fleet* f1, const Fleet* f2);
	bool operator == (const Fleet& fleet) const;

private:
	const uint _ownerID;
	const uint _source_planet_id;
	const uint _destination_planet_id;
	const uint _num_ships, _total_trip_length;
	uint _turns_remaining;
};


#endif /* FLEET_H_ */
