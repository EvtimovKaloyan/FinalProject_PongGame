#pragma once

#include <SDL.h>

#include <SDL_image.h>

#include <ctime>

class Ball {
public:
	Ball(int x, int y);

	SDL_Point getPosition();

	void setPosition(SDL_Point);

	SDL_Point getPace();

	void setPace(SDL_Point);

	SDL_Point setInitialDirection();

	void Reset();

	void Move();

private:
	SDL_Point position_, pace_;
};