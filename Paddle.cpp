#include "Paddle.h"

Paddle::Paddle(int x, int y) {
	position_.x = x;
	position_.y = y;
}

SDL_Point Paddle::getPosition()
{
	return this->position_;
}

void Paddle::setPosition(SDL_Point position)
{
	this->position_ = position;
}