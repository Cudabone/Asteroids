#pragma once
#include <vector>
#include "GameState.h"
#include "Ship.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "ScoreBoard.h"

namespace sf
{
    class RenderWindow;
}

class AsteroidsGame : public GameState 
{
    public:
    AsteroidsGame(sf::RenderWindow& InWindow);
    virtual ~AsteroidsGame() = default;

    virtual void HandleInput(float ElapsedTime) override;
    virtual void Update(float ElapsedTime) override;
    virtual void Render() override;

    private:
    void SpawnAsteroid();
    void HandleCollisions();

    Ship ship;
    ScoreBoard scoreboard;
    std::vector<Asteroid> asteroids;
    std::vector<Bullet> bullets;
};
