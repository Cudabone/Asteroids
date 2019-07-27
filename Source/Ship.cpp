#include "Ship.h"
#include "constants.h"
#include "util.h"

Ship::Ship()
	: shape(3), velocity(0.0f,0.0f)
{
	shape.setPoint(0, sf::Vector2f(1, 0));
	shape.setPoint(1, sf::Vector2f(0, 3));
	shape.setPoint(2, sf::Vector2f(2, 3));
	setOrigin(1, 1.5);
	setScale(30, 30);
 	setPosition(width / 2, height / 2);
}

void Ship::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(shape, states);
}

void Ship::accelerate(const float elapsedTime)
{
	velocity.x += ship_acceleration * sin(toRadians(getRotation()))*elapsedTime;
	velocity.y += ship_acceleration * -cos(toRadians(getRotation()))*elapsedTime;
}

void Ship::reset()
{
	setPosition(width/2,height/2);
	setRotation(0.0f);
	velocity = sf::Vector2f(0.0f, 0.0f);
}

void Ship::update(const float elapsedTime)
{
	sf::Vector2f pos = getPosition();
	pos.x += velocity.x*elapsedTime - 0.5f*ship_acceleration*square(elapsedTime);
	pos.y += velocity.y*elapsedTime - 0.5f*ship_acceleration*square(elapsedTime);
	wrapPosition(pos);
	setPosition(pos);
}
