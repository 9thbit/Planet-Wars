#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "Timer.h"
#include "Stats.h"

unsigned int runTimeOutTest(double timeout){
	Timer *timer1 = new Timer();
	unsigned int nr_checks = 0;
	
	timer1->SetTimeOut(timeout);
	//printf("Waiting for timeout...");
	while(!timer1->HasTimedOut()){
		//printf(".");
		nr_checks++;
	}
	printf("\nTimed out after %lld us. Checks: %d\n", timer1->MicrosElapsed(), nr_checks);
	delete timer1;
	return nr_checks;
}


int main(int argc, char * const argv[]){
	Stats stats;
	unsigned int nr_checks;
	double timeout = 0.5;
	
	for(int i=0;i<100;i++){
		nr_checks = runTimeOutTest(timeout);
		stats.addValue(static_cast<double>(nr_checks));
		std::cout << "NrChecks: " << nr_checks << std::endl;
	}
	
	std::cout << "Avg Checks: " << stats.getAverage() << std::endl;
	return 0;
}


