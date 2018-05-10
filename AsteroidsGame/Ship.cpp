#include "stdafx.h"
#include "Ship.hpp"
#include "constants.hpp"

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

void Ship::update()
{
	std::vector<sf::Vector2f> pts{ shape.getPoint(0),shape.getPoint(1),shape.getPoint(2) };
	for (auto &v : pts)
	{
		if (v.x < 0)
			v.x += width;
		if (v.x > width)
			v.x -= width;

		if (v.y < 0)
			v.y += height;
		if (v.y > height)
			v.y -= height;
	}
	for (std::size_t i = 0; i < pts.size(); ++i)
	{
		shape.setPoint(i, pts[i]);
	}
}