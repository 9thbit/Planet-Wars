//
//  Stats.h
//  planetwars_cpp1
//
//  Created by Barry Hurley on 21/02/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef STATS_H_
#define STATS_H_

#include "defines.h"

class Stats {
public:
	Stats() {nr_values=0;average=0;}
	void addValue(double val);
	double getAverage();
	
private:
	double average;
	uint nr_values;
};

#endif