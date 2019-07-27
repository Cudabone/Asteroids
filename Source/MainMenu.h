#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h"

class MainMenu : public GameState
{
    public:
    MainMenu(sf::RenderWindow& Window);
    virtual ~MainMenu() = default;

    virtual void HandleInput(float elapsedTime) override;
    virtual void Update(float elapsedTime) override;
    virtual void Render() override;

    private:
    sf::Font Font;
    sf::Text Title;
    sf::Text Subtitle;
};
