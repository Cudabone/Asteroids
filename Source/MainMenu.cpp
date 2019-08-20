#include "MainMenu.h"
#include "constants.h"
#include "RootDirectory.h"

MainMenu::MainMenu(sf::RenderWindow& Window)
: GameState(Window)
{
    if(!Font.loadFromFile(RootDirectory + "/Resource/8bit.ttf"))
    {

    }
    Title.setCharacterSize(200);
    Title.setString("Asteroids");
    sf::FloatRect rect = Title.getGlobalBounds();
    Title.setOrigin(rect.width / 2, rect.height / 2);
    Title.setPosition(width * 0.5f, height * 0.25f);
    Title.setFont(Font);
    //Title.setScale(5.0f,5.0f);

    Subtitle.setFont(Font);
    Subtitle.setScale(2.0f,2.0f);
    Subtitle.setString("Press Enter to Start");
}

void MainMenu::HandleInput(float elapsedTime)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        //set game state to Asteroids
    }
}

void MainMenu::Update(float elapsedTime)
{

}

void MainMenu::Render()
{
    Window.clear();
    Window.draw(Title); 
    Window.display();
}
