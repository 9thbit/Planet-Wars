CC = g++
CFLAGS = -O3 -funroll-loops -Wall -DDEBUG
DEFAULT = MyBot


MyBot: BaseBot.o CaseBasedBot.o Fleet.o Game.o GameState.o InferBot.o MinMaxBot.o order.o Planet.o Player.o point2d.o RageBot.o RandomBot.o ReinforcerBot.o Simple1Bot.o SniperBot.o Stats.o StringTokenizer.o Successor.o Timer.o MyBot.o
	$(CC) -O2 -lm -o MyBot BaseBot.o CaseBasedBot.o Fleet.o Game.o GameState.o InferBot.o MinMaxBot.o order.o Planet.o Player.o point2d.o RageBot.o RandomBot.o ReinforcerBot.o Simple1Bot.o SniperBot.o Stats.o StringTokenizer.o Successor.o Timer.o MyBot.o

TimerTest: TimerTest.o Timer.o Stats.o
	$(CC) -lm -o TimerTest TimerTest.o Stats.o Timer.o

BaseBot.o: BaseBot.cpp
	$(CC) $(CFLAGS) -c -o BaseBot.o BaseBot.cpp

CaseBasedBot.o: CaseBasedBot.cpp
	$(CC) $(CFLAGS) -c -o CaseBasedBot.o CaseBasedBot.cpp

Fleet.o: Fleet.cpp
	$(CC) $(CFLAGS) -c -o Fleet.o Fleet.cpp

Game.o: Game.cpp
	$(CC) $(CFLAGS) -c -o Game.o Game.cpp

GameState.o: GameState.cpp
	$(CC) $(CFLAGS) -c -o GameState.o GameState.cpp

InferBot.o: InferBot.cpp
	$(CC) $(CFLAGS) -c -o InferBot.o InferBot.cpp

MinMaxBot.o: MinMaxBot.cpp
	$(CC) $(CFLAGS) -c -o MinMaxBot.o MinMaxBot.cpp

order.o: order.cpp
	$(CC) $(CFLAGS) -c -o order.o order.cpp

Planet.o: Planet.cpp
	$(CC) $(CFLAGS) -c -o Planet.o Planet.cpp

Player.o: Player.cpp
	$(CC) $(CFLAGS) -c -o Player.o Player.cpp

point2d.o: point2d.cpp
	$(CC) $(CFLAGS) -c -o point2d.o point2d.cpp

RageBot.o: RageBot.cpp
	$(CC) $(CFLAGS) -c -o RageBot.o RageBot.cpp

RandomBot.o: RandomBot.cpp
	$(CC) $(CFLAGS) -c -o RandomBot.o RandomBot.cpp

ReinforcerBot.o: ReinforcerBot.cpp
	$(CC) $(CFLAGS) -c -o ReinforcerBot.o ReinforcerBot.cpp

Simple1Bot.o: Simple1Bot.cpp
	$(CC) $(CFLAGS) -c -o Simple1Bot.o Simple1Bot.cpp

SniperBot.o: SniperBot.cpp
	$(CC) $(CFLAGS) -c -o SniperBot.o SniperBot.cpp

StringTokenizer.o: StringTokenizer.cpp
	$(CC) $(CFLAGS) -c -o StringTokenizer.o StringTokenizer.cpp

Stats.o: Stats.cpp
	$(CC) $(CFLAGS) -c -o Stats.o Stats.cpp

Successor.o: Successor.cpp
	$(CC) $(CFLAGS) -c -o Successor.o Successor.cpp

Timer.o: Timer.cc
	$(CC) $(CFLAGS) -c -o Timer.o Timer.cc

MyBot.o: MyBot.cc
	$(CC) $(CFLAGS) -c -o MyBot.o MyBot.cc

TimerTest.o: TimerTest.cpp
	$(CC) -c -o TimerTest.o TimerTest.cpp


clean:
	rm -rf *.o MyBot


submission:
	mkdir submission
	cp *.cpp submission
	cp *.cc submission
	cp *.h submission
	rm submission/*Test.cpp
	zip -q submission.zip submission/*
	rm submission/*
	rmdir submission
	
