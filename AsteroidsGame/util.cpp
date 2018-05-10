#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "constants.hpp"
void wrapPosition(sf::Vector2f &pos)
{
	if (pos.x > width) pos.x -= width;
	if (pos.x < 0) pos.x += width;
	if (pos.y > height) pos.y -= height;
	if (pos.y < 0) pos.y += height;
}

inline float square(const float &f)
{
	return f*f;
}
inline float distance(const sf::Vector2f &a, const sf::Vector2f &b)
{
	return sqrt(square(b.x - a.x) + square(b.y - a.y));
}
constexpr float toRadians(const float degrees)
{
	return degrees * PI_TO_DEG;
}