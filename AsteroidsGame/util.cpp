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