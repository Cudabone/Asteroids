// AsteroidsGame.cpp : Defines the entry point for the console application.
//

//TODO:
// Break apart asteroids, separate them into sizes, spawn random sizes.
// Level progression (more asteroids per level)
// Score && Lives
// Start screen
// High scores
#include <SFML/Graphics.hpp>

#include "Game.h"
#include "MainMenu.h"
#include "AsteroidsGame.h"
#include "constants.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(width, height), "Asteroids");
	Game game(window);
	game.SetGameState(std::make_unique<AsteroidsGame>(window));
	//game.SetGameState(std::make_unique<MainMenu>(window));
	game.RunLoop();	
    return 0;
}
