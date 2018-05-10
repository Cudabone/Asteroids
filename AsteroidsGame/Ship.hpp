#ifndef SHIP_HPP
#define SHIP_HPP
#include <SFML/Graphics.hpp>

class Ship : public sf::Drawable , public sf::Transformable
{
public:
	Ship();
	void update();
	decltype(auto) getGlobalBounds()
	{
		return shape.getGlobalBounds();
	}
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::Vector2f velocity;
	sf::ConvexShape shape;
};
#endif