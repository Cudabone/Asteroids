// AsteroidsGame.cpp : Defines the entry point for the console application.
//

//TODO:
// Break apart asteroids, separate them into sizes, spawn random sizes.
// Level progression (more asteroids per level)
// Score && Lives
// Start screen
// High scores
#include <SFML/Graphics.hpp>
#include <cstddef>

#include <algorithm>
#include <cmath>
#include <string>
#include <iostream>
#include <random>
#include <vector>

#include "Ship.h"
#include "Bullet.h"
#include "constants.h"
#include "util.h"
#include "Asteroid.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(width, height), "Asteroids");

	Ship ship;
	std::vector<Asteroid> asteroids;
	std::vector<Bullet> bullets;

	asteroids.emplace_back();
	asteroids.emplace_back();

	//window.setFramerateLimit(60);

	sf::Clock clock;
	sf::Clock bullet_clock;
	while (window.isOpen())
	{
		//Draw all on screen items
		window.clear();
		window.draw(ship);
		for (const auto &a : asteroids)
			window.draw(a);
		for (const auto &b : bullets)
			window.draw(b);
		window.display();

		//Window Close Events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		sf::Time elapsedTime = clock.restart();

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
			break;
		}

		//Ship Movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			ship.rotate(elapsedTime.asSeconds() * -turning_rate);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			ship.rotate(elapsedTime.asSeconds() * turning_rate);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			ship.accelerate(elapsedTime.asSeconds());
		}

		//Shooting bullets
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if (bullet_clock.getElapsedTime().asSeconds() >= fire_rate)
			{
				bullets.emplace_back(ship.getPosition(), ship.getRotation());
				bullet_clock.restart();
			}
		}

		//framerate
		//std::cout << 1.f / elapsedTime.asSeconds() << std::endl;
		ship.update(elapsedTime.asSeconds());
		for (auto& a : asteroids)
		{
			a.update(elapsedTime.asSeconds());
		}
		for (auto &b : bullets)
		{
			b.update(elapsedTime.asSeconds());
		}

		for (size_t i = 0; i < bullets.size();)
		{
			auto& pos = bullets[i].getPosition();
			if (pos.x < 0 || pos.x > width || pos.y < 0 || pos.y > height)
			{
				std::swap(bullets[i], bullets.back());
				bullets.pop_back();
			}
			else ++i;
		}

		//Collision Detection
		for (size_t a_idx = 0; a_idx < asteroids.size();)
		{
			auto &a = asteroids[a_idx];
			auto &a_pos = a.getPosition();
			float a_radius = a.getRadius();
			//Bullets && Asteroids
			for (size_t b_idx = 0; b_idx < bullets.size();)
			{
				auto &b = bullets[b_idx];
				auto &b_pos = b.getPosition();
				if (distance_squared(a_pos, b_pos) < square(a_radius))
				{
					//Remove bullets
					std::swap(b, bullets.back());
					bullets.pop_back();

					//Remove asteroid
					std::swap(a, asteroids.back());
					asteroids.pop_back();
				}
				else ++b_idx;
			}
			//Ship && Asteroids
			if (distance_squared(a_pos, ship.getPosition()) < square(a_radius))
			{
				//Game over / lose life
				ship.reset();
				bullets.clear();
				asteroids.clear();
				asteroids.emplace_back();
				asteroids.emplace_back();
				break;
			}
			++a_idx;
		}
	}

    return 0;
}

