#include <SFML/Graphics.hpp>
#include <vector>

#include "Game.h"

Game::Game(sf::RenderWindow& InWindow)
: Window(InWindow)
{

}

void Game::RunLoop()
{
    while (Window.isOpen())
    {
        sf::Event event;
        while (Window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                Window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            Window.close();
            break;
        }

        //framerate
        //std::cout << 1.f / elapsedTime.asSeconds() << std::endl;

        GameState->HandleInput(Clock.getElapsedTime().asSeconds());
        GameState->Update(Clock.getElapsedTime().asSeconds());
        Clock.restart();
        GameState->Render();
    }
}
