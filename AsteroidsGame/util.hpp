#ifndef UTIL_H
#define UTIL_H
#include <SFML/Graphics.hpp>
void wrapPosition(sf::Vector2f &pos);
//Note to self: Constexpr functions implicitly inline
constexpr float toRadians(const float degrees);
//Maths
float square(const float &f);
float distance(const sf::Vector2f &a, const sf::Vector2f &b);
#endif