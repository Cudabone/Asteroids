#include "Asteroid.h"
#include "constants.h"
#include "util.h"

Asteroid::Asteroid(sf::Vector2f Position, sf::Vector2f Velocity, float Radius)
	: shape(Radius),
	velocity(Velocity)
{
	setOrigin(Radius, Radius);
	setPosition(Position);
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

std::vector<Asteroid> Asteroid::split()
{
	std::vector<Asteroid> outAsteroids;
	if(shape.getRadius() == asteroid_radius_smaller)
	{
		return outAsteroids;
	}

	float angle = toRadians(30);
	sf::Vector2f velocityA;
	velocityA.x = velocity.x*cosf(angle) - velocity.y*sinf(angle);
	velocityA.y = velocity.x*sinf(angle) + velocity.y*cosf(angle);

	angle = toRadians(-30);
	//sf::Vector2f velocityB(magnitude*cos(angle),magnitude*sin(angle));
	sf::Vector2f velocityB;
	velocityB.x = velocity.x*cosf(angle) - velocity.y*sinf(angle);
	velocityB.y = velocity.x*sinf(angle) + velocity.y*cosf(angle);

	Asteroid A(getPosition(),velocityA, asteroid_radius_smaller);
	Asteroid B(getPosition(),velocityB, asteroid_radius_smaller);

	outAsteroids.push_back(A);
	outAsteroids.push_back(B);
	
	return outAsteroids;
}
