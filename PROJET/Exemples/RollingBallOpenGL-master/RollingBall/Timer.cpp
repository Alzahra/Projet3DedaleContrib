#include "Timer.h"

Timer* Timer::instance;

Timer::Timer()
{
}

Timer::~Timer()
{
}

Timer* Timer::getInstance() {

	if (Timer::instance == NULL)
		Timer::instance = new Timer();
	return Timer::instance;
}

double Timer::getDelta() {

	return this->deltaTime;
}

void Timer::calcStart() {

	this->startTime = time(0);
	if (this->oldTime == NULL)
		this->deltaTime = this->secPerFrame / 1000;
	else
		this->deltaTime = difftime(this->startTime, this->oldTime); // too small magnitude; (almost) always is zero
	this->oldTime = this->startTime;
}

void Timer::sleep() {

	this->endTime = time(0);
	if (this->startTime != NULL) {
		double elapsedTime = difftime(this->endTime, this->startTime) * 1000;
		double sleepTime = this->secPerFrame - elapsedTime;
		/*if (sleepTime > 0)
			Sleep(sleepTime);*/
		/*wchar_t str[30];
		swprintf_s(str, 30, L"Sleep time: %f\n", sleepTime);
		OutputDebugString(str);*/
	}
}