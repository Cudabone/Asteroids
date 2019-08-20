#include "ScoreBoard.h"
#include "RootDirectory.h"
#include <string>

ScoreBoard::ScoreBoard()
{
    if(!Font.loadFromFile(RootDirectory + "/Resource/8bit.ttf"))
    {

    }
    ScoreText.setFont(Font);
    ScoreText.setCharacterSize(60);
}

void ScoreBoard::add(int Num)
{
    Score += Num;
}

void ScoreBoard::reset()
{
    Score = 0;
}

void ScoreBoard::update(float ElapsedTime)
{
    std::string text = "Score: " + std::to_string(Score);
    ScoreText.setString(text);
}

void ScoreBoard::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
	states.transform *= getTransform();
	target.draw(ScoreText, states);
}
