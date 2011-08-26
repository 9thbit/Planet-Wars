#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include "Game.h"
#include "InferBot.h"
#include "MinMaxBot.h"
#include "RageBot.h"
#include "RandomBot.h"
#include "Simple1Bot.h"
#include "SniperBot.h"
#include "order.h"
#include "Player.h"

using namespace std;

int main (int argc, char * const argv[]) {
	Game game;
	MinMaxBot bot(game.gameState(), PLAYER_1);
	//InferBot bot(game.gameState(), PLAYER_1);
	//RageBot bot(game.gameState(), PLAYER_1);
	//RandomBot bot(game.gameState(), PLAYER_1);
	//Simple1Bot bot(game.gameState(), PLAYER_1);
	//SniperBot bot(game.gameState(), PLAYER_1);
	Orders* botOrders;
	string currentLine;
	string mapData;
	uint turnCount = 1;
	while (true) {
		int c = cin.get();
		if(c==EOF)break;
		
		if(c=='\n'){
			if(currentLine.length()>=2 && currentLine.substr(0, 2)=="go"){
				std::cerr << "---------- TURN " << turnCount << " ----------" << endl;
				clock_t t = clock();
				botOrders = bot.doTurn();
				t = clock()-t;
				fprintf(stderr, "bot took %f to do turn.\n", (double)t/CLOCKS_PER_SEC);
				game.issueOrders(botOrders);
				game.finishTurn();
				for(uint i=0;i<botOrders->size();i++){
					delete botOrders->at(i);
				}
				botOrders->clear();
				turnCount++;
			} else {
				//std::cerr << "Received line: " << currentLine << std::endl;
				game.updateState(currentLine);
				
			}
			currentLine="";
		} else {
			currentLine += (char)c; //FIXME string concat expensive?
		}
	}
	
    return 0;
}
