#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Timer
{
private:
	Clock clock;

	int minutes;
	int seconds;

public:
	Timer();

	void restart();

	void update();

	string getTimeStr() const;
};

