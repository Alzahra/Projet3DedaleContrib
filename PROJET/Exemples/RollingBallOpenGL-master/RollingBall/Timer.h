#pragma once
#include "includes.h"

class Timer
{
private:
	time_t startTime, endTime, oldTime;
	double deltaTime;
	const double secPerFrame = 5;
	static Timer* instance;
public:
	Timer();
	~Timer();
	static Timer* getInstance();
	double getDelta();
	void calcStart();
	void sleep();
};

