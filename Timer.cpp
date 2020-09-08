#include "Timer.h"

Timer::Timer()
	: seconds(0), minutes(0) {}

void Timer::restart()
{
	clock.restart();
	seconds = 0;
	minutes = 0;
}

void Timer::update()
{
	seconds = (int)clock.getElapsedTime().asSeconds();
	if (seconds >= 60)
	{
		clock.restart();
		++minutes;
		seconds = 0;
	}
}

string Timer::getTimeStr() const
{
	string time(to_string(minutes) + ":");

	if (seconds < 10)
		time += "0";
	time += to_string(seconds);

	return time;
}
