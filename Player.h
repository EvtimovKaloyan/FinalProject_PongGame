#pragma once

#include <string>

#include "Paddle.h"

class Player {
public:
	Player(std::string name, int points, int x, int y);

	SDL_Point getPosition();

	void setPosition(SDL_Point);

	int getPoints();

	void setPoints(int);

private:
	std::string name_;
	int points_ = 0;

	Paddle paddle_;
};