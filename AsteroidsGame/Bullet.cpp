#include "stdafx.h"
#include "Bullet.hpp"
#include "constants.hpp"
#include "util.hpp"
constexpr float toRadians(const float degrees)
{
	return degrees * PI_TO_DEG;
}
//angle in degrees
Bullet::Bullet(const sf::Vector2f &pos, float degrees)
	:line(sf::Vector2f(bullet_width, bullet_height))
{
	setOrigin(bullet_width / 2, bullet_height / 2);
	setPosition(pos);
	setRotation(degrees);
	setScale(5, 5);
	velocity = sf::Vector2f(bullet_velocity * sin(toRadians(degrees)), 
							bullet_velocity * -cos(toRadians(degrees)));
}
void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(line, states);
}