// AsteroidsGame.cpp : Defines the entry point for the console application.
//

//TODO: Clean up ugly goto with restart method

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

//int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
int main()
{
start:
	sf::RenderWindow window(sf::VideoMode(width, height), "Asteroids");

	Ship ship;
	std::vector<Asteroid> asteroids;
	std::vector<Bullet> bullets;

	asteroids.emplace_back();
	
	//Draw Initial Objects
	window.draw(ship);
	for (auto &a : asteroids)
	{
		window.draw(a);
	}

	window.clear();
	window.display();
	//window.setFramerateLimit(60);

	sf::Clock clock;
	sf::Clock bullet_clock;
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
		
		for (int i = 0; i < bullets.size();)
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
		for (auto a_idx = 0; a_idx < asteroids.size();)
		{
			auto &a = asteroids[a_idx];
			auto &a_pos = a.getPosition();
			auto a_radius = a.getRadius();
			//Bullets && Asteroids
			for (int b_idx = 0; b_idx < bullets.size();)
			{
				auto &b = bullets[b_idx];
				auto &b_pos = b.getPosition();
				if (distance(a_pos, b_pos) < a_radius)
				{
					std::swap(b, bullets.back());
					bullets.pop_back();
				}
				else ++b_idx;
			}
			//Ship && Asteroids
			if (distance(a_pos, ship.getPosition()) < a_radius)
			{
				//Game over / lose life
				goto start;
			}
			++a_idx;
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

