// AsteroidsGame.cpp : Defines the entry point for the console application.
//

//TODO : Check where asteroid center point is: wrapping detection point seems off.

#include "stdafx.h"
#include <Windows.h>
#include <SFML/Graphics.hpp>
#include <cstddef>
#include <cstdlib>
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

sf::CircleShape generateAsteroid()
{
	float radius = 0.05f * width;
	sf::CircleShape a(radius);
	a.setOrigin(radius, radius);
	a.setPosition(sf::Vector2f(static_cast<float>(RNG(0,width)()),static_cast<float>(RNG(0,height)())));
	return a;
}

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	start:
	RNG rng(-25, 25);
	sf::RenderWindow window(sf::VideoMode(width, height), "Asteroids");
	Ship ship;
	sf::CircleShape a1(generateAsteroid());
	sf::Vector2f shipVel(0, 0);
	sf::Vector2f AsteroidVel(static_cast<float>(rng()),static_cast<float>(rng()));
	std::vector<Bullet> bullets;
	window.draw(ship);
	window.draw(a1);
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			ship.rotate(elapsedTime.asSeconds() * -360.0f);
			// move left...
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			ship.rotate(elapsedTime.asSeconds() * 360.0f);
			// move left...
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			shipVel.x += sin(toRadians(ship.getRotation()))*elapsedTime.asSeconds();
			shipVel.y += -cos(toRadians(ship.getRotation()))*elapsedTime.asSeconds();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			//shoot bullet along the axis of ship direction
			bullets.emplace_back(ship.getPosition(), ship.getRotation());
		}

		sf::Vector2f shipPos = ship.getPosition();
		sf::Vector2f a1Pos = a1.getPosition();
		shipPos.x += shipVel.x;
		shipPos.y += shipVel.y;
		a1Pos.x += AsteroidVel.x * elapsedTime.asSeconds();
		a1Pos.y += AsteroidVel.y * elapsedTime.asSeconds();

		for (auto &b : bullets)
		{
			auto& pos = b.getPosition();
			auto& vel = b.getVelocity();
			b.setPosition(pos.x + vel.x * elapsedTime.asSeconds(), 
						  pos.y + vel.y * elapsedTime.asSeconds());
		}
		//update position of the ship
		//wrap based on position
		
		wrapPosition(shipPos);
		wrapPosition(a1Pos);
		//if(ship.getPo)

		//ship.update();
		ship.setPosition(shipPos);
		a1.setPosition(a1Pos);

		shipPos = ship.getPosition();
		a1Pos = a1.getPosition();

		//auto shipBox = ship.getGlobalBounds();
		auto asteroidBox = a1.getGlobalBounds();
		//Collision Detection

		//First do bounding box calc to avoid the sqrt calc
	//	if (asteroidBox.contains(shipPos.x, shipPos.y))
		{
			if (distance(shipPos, a1Pos) < a1.getRadius())
			{
				goto start;
			}
		}
		/*
		for (auto it = bullets.begin(); it != bullets.end();)
		{
			if (asteroidBox.contains(it->getPosition()))
			{
				if (distance(it->getPosition(), a1Pos) < a1.getRadius())
				{
					it = bullets.erase(it);
					//remove bullet and now remove asteroids
				}
			}
			else ++it;
		}
		*/

		//Remove any bullets that have left the game screen
		for (auto it = bullets.begin(); it != bullets.end();)
		{
			auto& pos = it->getPosition();

			if (pos.x < 0 || pos.x > width || pos.y < 0 || pos.y > height)
			{
				//it = bullets.erase(it);
				std::swap(*it, bullets.back());
				bullets.pop_back();
			}
			else ++it;
		}

		window.clear();
		window.draw(a1);
		window.draw(ship);
		for (auto &b : bullets)
			window.draw(b);
		window.display();
	}

    return 0;
}

