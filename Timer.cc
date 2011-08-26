#include "Timer.h"

/*
 * The timer uses gettimeofday() to get the current time.
 */

Timer::Timer(){
	gTimeOut = 0;
	gStartTime = 0;
}


void Timer::SetTimeOut(double seconds) {
	/*timeval startTime;
	gettimeofday(&startTime, NULL);

	gStartTime = startTime.tv_sec*1000000 + startTime.tv_usec;
	gTimeOut = gStartTime + static_cast<long long>(seconds * 1000000.0);*/
	start = clock();
	timeout = start + seconds*CLOCKS_PER_SEC;
}

bool Timer::HasTimedOut() {
	/*timeval currentTime;
	gettimeofday(&currentTime, NULL);

	return (currentTime.tv_sec*1000000 + currentTime.tv_usec) > gTimeOut;*/
	return clock()>timeout;
}

long long Timer::MillisElapsed() {
    return static_cast<long long>(MicrosElapsed()/1000.0 + 0.5);
}

long long Timer::MicrosElapsed(){
	/*timeval currentTime;
	gettimeofday(&currentTime, NULL);
	
	const long long currentMicroseconds = currentTime.tv_sec*1000000 + currentTime.tv_usec;
    const long long microsElapsed = (currentMicroseconds - gStartTime);
    return microsElapsed;*/
	return ((clock()-start)*1000000)/CLOCKS_PER_SEC;
}