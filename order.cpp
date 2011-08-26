#include "order.h"
#include "Player.h"
#include "Planet.h"
#include <iostream>

Order::Order(uint source_planet_id, uint destination_planet_id, uint numberOfShips) :
    source_planet_id(source_planet_id),
    destination_planet_id(destination_planet_id),
    shipsCount(numberOfShips)
{
}

bool Order::isValid() const {
    return (source_planet_id!=destination_planet_id) // Source can not be equal to destination
         //&& (sourcePlanet->owner()->isMe())                             // I must own the source planet
         && (shipsCount > 0)                                            // I must send more then 0 ships
         //FIXME&& (sourcePlanet->ships_count >= shipsCount)                  // The source planet must have enought ships
         ;
}

#ifdef DEBUG
std::ostream& operator << (std::ostream& out, const Order& o){
	out << "O(" << o.shipsCount << ") " << o.source_planet_id << "->" << o.destination_planet_id;
	return out;
}
#endif

bool Order::operator == (const Order& o) const{
	return source_planet_id==o.source_planet_id
		&& destination_planet_id==o.destination_planet_id
		&& shipsCount==o.shipsCount;
}
