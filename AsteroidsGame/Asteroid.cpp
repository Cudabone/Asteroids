#include "stdafx.h"
#include "Asteroid.hpp"
#include "constants.hpp"
#include "util.hpp"

Asteroid::Asteroid()
	:shape(asteroid_radius), 
	velocity(static_cast<float>(RNG(-.1f*width,.1f*width)()), static_cast<float>(RNG(-.1f*width,.1f*width)()))
{
	setOrigin(asteroid_radius, asteroid_radius);
	setPosition(sf::Vector2f(static_cast<float>(RNG(0, width)()), static_cast<float>(RNG(0, height)())));
}

void Asteroid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(shape, states);
}

void Asteroid::update(const float elapsedTime)
{
	sf::Vector2f pos = getPosition();
	pos.x += velocity.x * elapsedTime;
	pos.y += velocity.x * elapsedTime;
	wrapPosition(pos);
	setPosition(pos);
}