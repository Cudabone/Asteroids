// AsteroidsGame.cpp : Defines the entry point for the console application.
//

//TODO: Limit bullet fire rate using sf::Time;
#include "stdafx.h"
#include <Windows.h>
#include <SFML/Graphics.hpp>
#include <cstddef>

#include <algorithm>
#include <cmath>
#include <string>
#include <iostream>
#include <random>
#include <vector>

#include "Ship.hpp"
#include "Bullet.hpp"
#include "constants.hpp"
#include "util.hpp"
#include "Asteroid.hpp"

struct rational
{
	std::size_t num = 0;
	std::size_t den = 1;
};
constexpr rational reduce(rational r)
{
	for (int i = min(r.num, r.den); i >= 0; i++)
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

sf::CircleShape generateAsteroid()
{
	float radius = 0.05f * width;
	sf::CircleShape a(radius);
	a.setOrigin(radius, radius);
	a.setPosition(sf::Vector2f(static_cast<float>(RNG(0,width)()),static_cast<float>(RNG(0,height)())));
	return a;
}

//int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
int main()
{
start:
	RNG rng(-25, 25);
	sf::RenderWindow window(sf::VideoMode(width, height), "Asteroids");
	Ship ship;
	sf::Vector2f shipVel(0, 0);
	std::vector<Asteroid> asteroids;

	sf::Vector2f AsteroidVel(static_cast<float>(rng()),static_cast<float>(rng()));
	std::vector<Bullet> bullets;
	
	//Draw Initial Objects
	window.draw(ship);
	//Draw Asteroids
	for (auto &a : asteroids)
	{
		window.draw(a);
	}

	window.clear();
	window.display();
	//window.setFramerateLimit(60);

	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		sf::Time elapsedTime = clock.restart();

		//Ship Movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			ship.rotate(elapsedTime.asSeconds() * -360.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			ship.rotate(elapsedTime.asSeconds() * 360.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			ship.update(elapsedTime.asSeconds());
		}

		//Shooting bullets
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			bullets.emplace_back(ship.getPosition(), ship.getRotation());
		}

		//framerate
		//std::cout << 1.f / elapsedTime.asSeconds() << std::endl;
	
		for (auto &b : bullets)
		{
			b.update(elapsedTime.asSeconds());
		}
		//update position of the ship
		//wrap based on position

		//auto shipBox = ship.getGlobalBounds();
		//auto asteroidBox = a1.getGlobalBounds();
		//Collision Detection

		//First do bounding box calc to avoid the sqrt calc
		/*
		if (asteroidBox.contains(shipPos.x , shipPos.y))
		{
			if (distance(shipPos, a1Pos) < a1.getRadius())
			{
				goto start;
			}
		}
		*/

		//Remove any bullets which go off screen
		for (auto it = bullets.begin(); it != bullets.end();)
		{
			auto& pos = it->getPosition();
			if (pos.x < 0 || pos.x > width || pos.y < 0 || pos.y > height)
			{
				std::swap(*it, bullets.back());
				bullets.pop_back();
			}
			else ++it;
		}

		//Collision Detection
		for (auto a_it = asteroids.begin(); a_it != asteroids.end();)
		{
			auto &a_pos = a_it->getPosition();
			auto a_rad = a_it->getRadius();
			for (auto b_it = bullets.begin(); b_it != bullets.end();)
			{
				auto &b_pos = b_it->getPosition();
				if (distance(a_pos, b_pos) < a_it->getRadius())
				{
					std::swap(*b_it, bullets.back());
					bullets.pop_back();
				}
				else ++b_it;
			}
			if (distance(a_pos, ship.getPosition()) < a_rad)
			{
				//Game over / lose life
				goto start;
			}
			++a_it;
		}
		
		window.clear();

		//Redraw all on screen items
		window.draw(ship);
		for (const auto &a : asteroids)
			window.draw(a);
		for (const auto &b : bullets)
			window.draw(b);
		window.display();
	}

    return 0;
}

