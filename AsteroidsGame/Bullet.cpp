#include "stdafx.h"
#include "Bullet.hpp"
#include "constants.hpp"
#include "util.hpp"
#include <cmath>
//angle in degrees
Bullet::Bullet(const sf::Vector2f &pos, float degrees)
	:line(sf::Vector2f(bullet_width, bullet_height)),
	velocity(bullet_velocity * sin(toRadians(degrees)), bullet_velocity * -cos(toRadians(degrees)))
{
	setOrigin(bullet_width / 2, bullet_height / 2);
	setPosition(pos);
	setRotation(degrees);
	setScale(5, 5);
}
void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(line, states);
}
//Pass in time since last update in seconds
void Bullet::update(const float elapsedTime)
{
	auto& pos = getPosition();
	setPosition(pos.x + velocity.x * elapsedTime, pos.y + velocity.y * elapsedTime);
}