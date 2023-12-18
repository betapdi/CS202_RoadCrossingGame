#include "CENTITY.h"

void CENTITY::setVelocity(sf::Vector2f velocity)
{
	mVelocity = velocity;
}

void CENTITY::setVelocity(float vx, float vy)
{
	mVelocity.x = vx;
	mVelocity.y = vy;
}

void CENTITY::setInitialPosition(sf::Vector2f pos) {
	mPosition = pos;
}

sf::Vector2f CENTITY::getVelocity() const
{
	return mVelocity;
}

void CENTITY::updateCurrent(float deltaTime)
{
	move(mVelocity * deltaTime);
}