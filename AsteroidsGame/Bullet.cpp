#include "stdafx.h"
#include "Bullet.hpp"
#include "constants.hpp"

//If given angle, no calculation, if given unit vector must do arctan/arccos/arcsinh
//angle in degrees
Bullet::Bullet(const sf::Vector2f &pos, float angle)
	:line(sf::Vector2f(bullet_width, bullet_height))
{
	line.setOrigin(bullet_width / 2, bullet_height / 2);
	line.setPosition(pos);
	line.setRotation(angle);
	line.setScale(5, 5);
	this.velocity()
}
void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(line, states);
}
sf::Vector2f &Bullet::getVelocity()
{
	return velocity;
}
