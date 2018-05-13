#ifndef UTIL_HPP
#define UTIL_HPP
#include <SFML/Graphics.hpp>
#include "constants.hpp"
#include <random>
void wrapPosition(sf::Vector2f &pos);
//Note to self: Constexpr functions implicitly inline and inlines 
//must be defined in every TU that needs it -> define in header

struct rational;
constexpr rational reduce(rational r);

struct aspect_ratio;

//Random Number generator
struct RNG
{
	RNG(int start, int end)
		: rd(), gen(rd()), dist(start, end)
	{}
	
	decltype(auto) operator() ()
	{
		return dist(gen);
	}
private:
	std::random_device rd; //non-deterministic random seed
	std::mt19937 gen; //rng
	std::uniform_int_distribution<> dist; // All numbers equally likely
};

//Maths
constexpr float toRadians(const float degrees)
{
	return degrees * PI_TO_DEG;
}
inline float square(const float &f)
{
	return f * f;
}
inline float distance(const sf::Vector2f &a, const sf::Vector2f &b)
{
	return sqrt(square(b.x - a.x) + square(b.y - a.y));
}
#endif