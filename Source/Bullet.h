#pragma once
#include <SFML/Graphics.hpp>

class Bullet : public sf::Drawable, public sf::Transformable
{
public:
	Bullet(const sf::Vector2f &pos, float degrees);

	void update(const float elapsedTime);

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	sf::RectangleShape line;
	sf::Vector2f velocity;
};
