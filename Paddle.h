#pragma once

#include <SDL.h>

#include <SDL_image.h>

class Paddle {
public:
	Paddle(int x, int y);

	SDL_Point getPosition();
	
	void setPosition(SDL_Point);

private:
	SDL_Point position_;
};