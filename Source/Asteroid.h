#pragma once
#include <SFML/Graphics.hpp>
class Asteroid : public sf::Drawable, public sf::Transformable
{
public:
	Asteroid();

	void update(const float elapsedTime);
	float getRadius() const
	{
		return shape.getRadius();
	}
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::CircleShape shape;
	sf::Vector2f velocity;
};
