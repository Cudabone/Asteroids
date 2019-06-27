#include "Asteroid.h"
#include "constants.h"
#include "util.h"

Asteroid::Asteroid()
	:shape(asteroid_radius), 
	velocity(Random::Get(-asteroid_max_velocity, asteroid_max_velocity),
			 Random::Get(-asteroid_max_velocity, asteroid_max_velocity))
{
	setOrigin(asteroid_radius, asteroid_radius);
	//setPosition(sf::Vector2f(static_cast<float>(RNG(0, width)()), static_cast<float>(RNG(0, height)())));

	float x = static_cast<float>(Random::Get(0, width));
	float y;
	if (x > center_x - safety_radius && x < center_x + safety_radius)
	{
		float interval;
		if (Random::Get(0, 1) == 0)
		{
			//"Top" half of circle
			interval = sqrt(square(safety_radius) - square(x - center_x)) + center_y;
			y = Random::Get(interval, static_cast<float>(height));
		}
		else
		{
			//"Bottom" half of circle
			interval = -sqrt(square(safety_radius) - square(x - center_x)) + center_y;
			y = Random::Get(0.0f, interval);
		}
	}
	else
	{
		y = static_cast<float>(Random::Get(0, height));
	}

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
	pos.y += velocity.y * elapsedTime;
	wrapPosition(pos);
	setPosition(pos);
}