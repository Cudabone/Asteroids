#pragma once
#include <SFML/Graphics.hpp>

class ScoreBoard : public sf::Drawable, public sf::Transformable
{
    public:
    ScoreBoard();

    void add(int Num);
    void update(float ElapsedTime);
    void reset();

    protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
    int Score = 0; 
    sf::Text ScoreText;
    sf::Font Font;
};
