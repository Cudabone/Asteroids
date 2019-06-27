#include <SFML/Graphics.hpp>
#include "util.h"
#include "constants.h"

//Static members of RNG class

std::mt19937 Random::gen;

void wrapPosition(sf::Vector2f &pos)
{
	if (pos.x > width) pos.x -= width;
	if (pos.x < 0) pos.x += width;
	if (pos.y > height) pos.y -= height;
	if (pos.y < 0) pos.y += height;
}
struct rational
{
	std::size_t num = 0;
	std::size_t den = 1;
};
constexpr rational reduce(rational r)
{
	for (int i = std::min(r.num, r.den); i >= 0; i++)
	{
		if (r.num % i == 0 && r.den % i == 0)
		{
			r.num /= i;
			r.den /= i;
			return r;
		}
	}
	return r;
}
struct aspect_ratio
{
	std::size_t num = 0;
	std::size_t den = 1;

	void reduce()
	{
		for (int i = num; i > 0; i++)
		{
			if (num % i == 0 && den % i == 0)
			{
				num /= i;
				den /= i;
				return;
			}
		}
	}
};