#pragma once
#include <memory>
#include <utility>
#include "GameState.h"
#include "Ship.h"
#include "AsteroidsGame.h"
class Bullet;

class Game
{
    public:
    Game(sf::RenderWindow& InWindow);
    void RunLoop();
    void SetGameState(std::unique_ptr<GameState>&& InGameState) { GameState = std::move(InGameState); }

    private:
    sf::Clock Clock;
    sf::RenderWindow& Window;
    std::unique_ptr<GameState> GameState;
};
