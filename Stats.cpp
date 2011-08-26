//
//  Stats.cpp
//  planetwars_cpp1
//
//  Created by Barry Hurley on 21/02/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Stats.h"

#define min(x,y) (x>y) ? y : x

void Stats::addValue(double val){
	/*if(nr_values==0){
		average = val;
	} else {
		average = ((average*nr_values)+val)/(nr_values+1);
	}
	
	nr_values++;*/
	//int temp_nr_values = min(nr_values, 2);
	//average = (average*temp_nr_values+val)/(++temp_nr_values);
	//nr_values++;
	average = average>0 && average < val ? average : val;
}

double Stats::getAverage(){
	return average;
}