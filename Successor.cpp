/*
 *  Successor.cpp
 *  planetwars_cpp1
 *
 *  Created by Barry Hurley on 17/11/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Successor.h"
#include "GameState.h"
#include "order.h"
#include <iostream>

Successor::~Successor(){
	//std::cerr << "in successor destructor" << std::endl;
	delete gamestate;
	for(uint i=0;i<orders->size();i++){
		delete orders->at(i);
	}
	delete orders;
}
#ifdef DEBUG
std::ostream& operator << (std::ostream& out, const Successor& s){
	out << "Successor. Gamestate: " << s.gamestate << " Orders:" << std::endl;
	for(uint i=0;i< s.orders->size();i++){
		out << s.orders->at(i) << std::endl;
	}
	return out;
}
#endif
