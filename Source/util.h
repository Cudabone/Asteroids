#pragma once
#include <SFML/Graphics.hpp>
#include "constants.h"
#include <random>

void wrapPosition(sf::Vector2f &pos);

struct rational;
constexpr rational reduce(rational r);

struct aspect_ratio;

//Random Number generator
struct Random
{
	static float Get( float start, float end )
	{
		std::uniform_real_distribution<float> dist( start, end );
		return dist( gen );
	}

	static int Get( int start, int end )
	{
		std::uniform_int_distribution<> dist( start, end );
		return dist( gen );
	}

private:
	static std::mt19937 gen; //Generator
};

//Maths
constexpr float toRadians(const float degrees)
{
	return degrees * DEG_TO_RAD;
}
template<typename T>
inline T square(const T& t)
{
	return t * t;
}
inline float distance(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return sqrt(square(b.x - a.x) + square(b.y - a.y));
}
inline float distance_squared(const sf::Vector2f &a, const sf::Vector2f &b)
{
	return square(b.x - a.x) + square(b.y - a.y);
}
