#ifndef ORDER_H
#define ORDER_H

#include "defines.h"

class Order {
#ifdef DEBUG
	friend std::ostream& operator<<(std::ostream& out, const Order& o);
#endif
public:
    Order(uint source_planet_id, uint destination_planet_id, uint numberOfShips);
	bool operator == (const Order& o) const;

    uint source_planet_id;
    uint destination_planet_id;

    const uint shipsCount;

    bool isValid() const;
};

#endif // ORDER_H
