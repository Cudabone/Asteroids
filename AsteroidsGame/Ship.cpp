#include "stdafx.h"
#include "Ship.hpp"
#include "constants.hpp"
#include "util.hpp"

Ship::Ship()
	: shape(3), velocity(0.0f,0.0f)
{
	shape.setPoint(0, sf::Vector2f(1, 0));
	shape.setPoint(1, sf::Vector2f(0, 3));
	shape.setPoint(2, sf::Vector2f(2, 3));
	setOrigin(1, 1.5);
	setScale(30, 30);
 	setPosition(width / 2, height / 2);
	//setRotation(0.0f);
}
void Ship::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(shape, states);
}

void Ship::update(const float elapsedTime)
{
	velocity.x += sin(toRadians(getRotation()))*elapsedTime;
	velocity.y += -cos(toRadians(getRotation()))*elapsedTime;
	sf::Vector2f pos = getPosition();
	pos.x += velocity.x;
	pos.y += velocity.y;
	wrapPosition(pos);
	setPosition(pos);
}