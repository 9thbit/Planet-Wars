/*
 *  defines.h
 *  planetwars_cpp1
 *
 *  Created by Barry Hurley on 09/11/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef DEFINES_H
#define DEFINES_H

#include <vector>
#include <algorithm>
#include <cmath>

class CaseBasedBot;
class BaseBot;
class InferBot;
class Game;
class GameState;
class Planet;
class Fleet;
class Order;
class Player;
class Timer;
class Stats;
struct Successor;
template<typename Type> class Point2D;

typedef unsigned int uint;
typedef Point2D<double> Point;

typedef std::vector<Planet*> Planets;
typedef std::vector<Fleet*> Fleets;
typedef std::vector<Order*> Orders;
typedef std::vector<Player*> Players;
typedef std::vector<BaseBot*> Bots;
typedef std::vector<Successor*> Successors;
typedef std::vector<GameState*> GameStates;

#define NUM_PLAYERS 3
#define PLAYER_NEUTRAL 0
#define PLAYER_1 1
#define PLAYER_2 2

#endif // DEFINES_H
