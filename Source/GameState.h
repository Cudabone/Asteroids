#pragma once

namespace sf
{
    class RenderWindow;
}

class GameState
{
    public:
    GameState(sf::RenderWindow& InWindow) 
    : Window(InWindow) {}

    GameState(const GameState& InGameState) = default;
    GameState& operator=(const GameState& InGameState) = default;
    GameState(GameState&& InGameState) = default;
    GameState& operator=(GameState&& InGameState) = default;

    virtual ~GameState() = default;

    virtual void HandleInput(float elapsedTime) = 0;
    virtual void Update(float elapsedTime) = 0;
    virtual void Render() = 0;

    protected:
    sf::RenderWindow& Window;
};
