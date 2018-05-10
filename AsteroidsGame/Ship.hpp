#ifndef SHIP_HPP
#define SHIP_HPP
#include <SFML/Graphics.hpp>

class Ship : public sf::Drawable , public sf::Transformable
{
public:
	Ship();
	void update(const float elapsedTime);
	decltype(auto) getGlobalBounds()
	{
		return shape.getGlobalBounds();
	}

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::ConvexShape shape;
	sf::Vector2f velocity;
};
#endif