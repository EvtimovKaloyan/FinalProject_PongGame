#include "Ball.h"
#include <iostream>

Ball::Ball(int x, int y)
{
	position_.x = x;
	position_.y = y;
	SDL_Point tempPace = this->setInitialDirection();
	this->setPace(tempPace);
}

SDL_Point Ball::getPosition()
{
	return this->position_;
}

void Ball::setPosition(SDL_Point position)
{
	this->position_ = position;
}

SDL_Point Ball::getPace()
{
	return this->pace_;
}

void Ball::setPace(SDL_Point pace)
{
	this->pace_ = pace;
}

SDL_Point Ball::setInitialDirection()
{
	int directionIndicator = time(NULL) % 4;
	
	int xDirection, yDirection;

	switch (directionIndicator)
	{
	case 0:
		xDirection = 1;
		yDirection = 1;
		break;
	case 1:
		xDirection = 1;
		yDirection = -1;
		break;
	case 2:
		xDirection = -1;
		yDirection = -1;
		break;
	case 3:
		xDirection = -1;
		yDirection = 1;
	default:
		break;
	}

	int currentSecond = time(NULL) % 10;
	while (currentSecond == 0)
	{
		currentSecond = time(NULL) % 10;
	}

	SDL_Point pace;
		
	switch (currentSecond)
	{
	case 1:
		pace.x = xDirection * 2;
		pace.y = yDirection * 2;
		break;
	case 2:
		pace.x = xDirection * 2;
		pace.y = yDirection * 1;
		break;
	case 3:
		pace.x = xDirection * 1;
		pace.y = yDirection * 2;
		break;
	case 4:
		pace.x = xDirection * 3;
		pace.y = yDirection * 1;
		break;
	case 5:
		pace.x = xDirection * 1;
		pace.y = yDirection * 3;
		break;
	case 6:
		pace.x = xDirection * 3;
		pace.y = yDirection * 2;
		break;
	case 7:
		pace.x = xDirection * 2;
		pace.y = yDirection * 3;
		break;
	case 8:
		pace.x = xDirection * 4;
		pace.y = yDirection * 1;
		break;
	case 9:
		pace.x = xDirection * 1;
		pace.y = yDirection * 4;
		break;
	default:
		break;
	}

	return pace;
}

void Ball::Reset()
{

}

void Ball::Move()
{
	SDL_Point nextPosition;
	nextPosition.x = this->getPosition().x + this->getPace().x;
	nextPosition.y = this->getPosition().y + this->getPace().y;

	this->setPosition(nextPosition);

	SDL_Point currentPace = this->getPace();
	SDL_Point currentPosition = this->getPosition();

	if (currentPosition.y <= 0 || currentPosition.y >= 582)
	{
		currentPace.y *= -1;
		this->setPace(currentPace);
	}
	
	if (currentPace.x > 0 && currentPosition.x >= 516 && currentPosition.x <= 542 && currentPosition.y >= 177 && currentPosition.y <= 406)
	{
		currentPace.x *= -1;
		this->setPace(currentPace);
	}

	if (currentPace.x < 0 && currentPosition.x <= 556 && currentPosition.x >= 530 && currentPosition.y >= 177 && currentPosition.y <= 406)
	{
		currentPace.x *= -1;
		this->setPace(currentPace);
	}
	
	SDL_Delay(5);
}