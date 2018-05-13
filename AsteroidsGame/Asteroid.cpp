#include "stdafx.h"
#include "Asteroid.hpp"
#include "constants.hpp"
#include "util.hpp"

Asteroid::Asteroid()
	:shape(asteroid_radius), 
	velocity(static_cast<float>(RNG(-.1f*width,.1f*width)()), static_cast<float>(RNG(-.1f*width,.1f*width)()))
{
	setOrigin(asteroid_radius, asteroid_radius);
	//setPosition(sf::Vector2f(static_cast<float>(RNG(0, width)()), static_cast<float>(RNG(0, height)())));

	float x = static_cast<float>(RNG(0, width)());
	float y;
	if (x > center_x - safety_radius && x < center_x + safety_radius)
	{
		int interval;
		if (RNG(0, 1)() == 0)
		{
			//"Top" half of circle
			interval = sqrt(square(safety_radius) - square(x - center_x)) + center_y;
			y = static_cast<float>(RNG(interval, height)());
		}
		else
		{
			//"Bottom" half of circle
			interval = -sqrt(square(safety_radius) - square(x - center_x)) + center_y;
			y = static_cast<float>(RNG(0, interval)());
		}
	}
	else
		y = static_cast<float>(RNG(0, height)());

	setPosition(x, y);
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