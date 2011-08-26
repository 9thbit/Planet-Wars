/*
 *  StringTokenizer.h
 *  planetwars_cpp1
 *
 *  Created by Barry Hurley on 10/11/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef STRINGTOKENIZER_H_
#define STRINGTOKENIZER_H_

#include <vector>
#include <string>

class StringTokenizer{
public:
	static void split(const std::string &s, char delim, std::vector<std::string> &elems);
	static std::vector<std::string> split(const std::string &s, char delim);
	
	
private:
	
	StringTokenizer();
};

#endif
