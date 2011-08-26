/*
 *  Planet.h
 *  planetwars_cpp1
 *
 *  Created by Barry Hurley on 09/11/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef PLANET_H_
#define PLANET_H_

#include "defines.h"
#include "point2d.h"

class Planet {
public:
	Planet(uint planetID, uint shipsCount, uint growthRate, Point coordinate, uint ownerID);
	Planet(const Planet& p);
	//virtual ~Planet();
	const uint planetID() const;
    //uint shipsCount() const;
    uint growthRate() const;
	Point coordinate() const;
	const uint OwnerID() const;
	void updateDetails(uint new_ships_count, uint growth_rate, const uint ownerID);
	uint simpleShipsCountPrediction(uint nr_turns) const;
	uint simpleShipsAvailable(GameState* gamestate, uint myEnemyID);
	void advanceState(uint nr_turns, Fleets* arrivingFleets);
	bool closerPlanetToMe(const Planet* p1, const Planet* p2);
	double compareTo(const Planet *p2) const;
	static bool compareShipsCount(const Planet* p1, const Planet* p2);
    bool operator == (const Planet& p2) const;
    bool operator != (const Planet& p2) const;
	uint ships_count;
	
private:
	const uint _planet_id;
	//uint _ships_count;
	uint _growth_rate;
	Point _coordinate;
	uint _ownerID;
};


#endif /* PLANET_H_ */
