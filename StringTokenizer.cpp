/*
 *  StringTokenizer.cpp
 *  planetwars_cpp1
 *
 *  Created by Barry Hurley on 10/11/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "StringTokenizer.h"
#include <sstream>

void StringTokenizer::split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while(std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
}


std::vector<std::string> StringTokenizer::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
	StringTokenizer::split(s, delim, elems);
    return elems;
}
