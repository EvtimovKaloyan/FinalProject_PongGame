#include "Player.h"

Player::Player(std::string name, int points, int x, int y) 
	:	name_(name),
		points_(points),
		paddle_(x, y)
{}

SDL_Point Player::getPosition()
{
	return this->paddle_.getPosition();
}

void Player::setPosition(SDL_Point position)
{
	this->paddle_.setPosition(position);
}

int Player::getPoints()
{
	return this->points_;
}

void Player::setPoints(int points)
{
	this->points_ = points;
}