#include <SFML/Graphics.hpp>
#include "AsteroidsGame.h"
#include "Asteroid.h"
#include "Ship.h"
#include "Bullet.h"
#include "constants.h"
#include "util.h"

AsteroidsGame::AsteroidsGame(sf::RenderWindow& InWindow)
: GameState(InWindow) 
{
    SpawnAsteroid();
    SpawnAsteroid();
}

void AsteroidsGame::HandleInput(float ElapsedTime)
{
    static sf::Clock bulletClock;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        ship.rotate(ElapsedTime * -turning_rate);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        ship.rotate(ElapsedTime * turning_rate);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        ship.accelerate(ElapsedTime);
    }

    //Shooting bullets
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        if (bulletClock.getElapsedTime().asSeconds() >= fire_rate)
        {
            bullets.emplace_back(ship.getPosition(), ship.getRotation());
            bulletClock.restart();
        }
    }
}

void AsteroidsGame::Update(float ElapsedTime)
{
    ship.update(ElapsedTime);
    for (Asteroid& a : asteroids)
    {
        a.update(ElapsedTime);
    }
    for (Bullet& b : bullets)
    {
        b.update(ElapsedTime);
    }
    scoreboard.update(ElapsedTime);

    HandleCollisions();
}

void AsteroidsGame::Render()
{
    Window.clear();
    Window.draw(ship);
    for (const auto &a : asteroids)
        Window.draw(a);
    for (const auto &b : bullets)
        Window.draw(b);
    Window.draw(scoreboard);
    Window.display();
}

void AsteroidsGame::SpawnAsteroid()
{
    sf::Vector2f Velocity(Random::Get(-asteroid_max_velocity, asteroid_max_velocity),
			 Random::Get(-asteroid_max_velocity, asteroid_max_velocity));
    
    //Create a safety radius around the player where the asteroid cannot spawn.
    sf::Vector2f shipPos = ship.getPosition();
    sf::Vector2f Position;
	Position.x = static_cast<float>(Random::Get(0, width));
	if (Position.x > shipPos.x - safety_radius && Position.x < shipPos.x + safety_radius)
	{
		float interval;
		if (Random::Get(0, 1) == 0)
		{
			//"Top" half of circle
			interval = sqrt(square(safety_radius) - square(Position.x - shipPos.x)) + shipPos.y;
			Position.y = Random::Get(interval, static_cast<float>(height));
		}
		else
		{
			//"Bottom" half of circle
			interval = -sqrt(square(safety_radius) - square(Position.x - shipPos.x)) + shipPos.y;
			Position.y = Random::Get(0.0f, interval);
		}
	}
	else
	{
		Position.y = static_cast<float>(Random::Get(0, height));
	}
    asteroids.emplace_back(Position,Velocity, asteroid_radius);
}

void AsteroidsGame::HandleCollisions()
{
    //Remove bullets that have left the scene
    for (size_t i = 0; i < bullets.size();)
    {
        auto &pos = bullets[i].getPosition();
        sf::Vector2u screenDimensions = Window.getSize();
        if (pos.x < 0 || pos.x > screenDimensions.x || pos.y < 0 || pos.y > screenDimensions.y)
        {
            std::swap(bullets[i], bullets.back());
            bullets.pop_back();
        }
        else
            ++i;
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
                scoreboard.add(100);

                //Remove bullets
                std::swap(b, bullets.back());
                bullets.pop_back();

                //Split asteroid.
                //Remove asteroid
                std::vector<Asteroid> splitAsteroids = a.split();

                std::swap(a, asteroids.back());
                asteroids.pop_back();

                for(Asteroid& a : splitAsteroids)
                {
                    asteroids.emplace_back(a);
                }

                if(asteroids.size() < 10)
                {
                    SpawnAsteroid();
                }
            }
            else
                ++b_idx;
        }
        //Ship && Asteroids
        if (distance_squared(a_pos, ship.getPosition()) < square(a_radius))
        {
            //Game over / lose life
            ship.reset();
            bullets.clear();
            asteroids.clear();
            scoreboard.reset();
            SpawnAsteroid();
            SpawnAsteroid();
            break;
        }
        ++a_idx;
    }
}
