#pragma once
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
	void Ship::accelerate(const float elapsedTime);
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::ConvexShape shape;
	sf::Vector2f velocity;
};
