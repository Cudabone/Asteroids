#ifndef BULLET_HPP
#define BULLET_HPP
#include <SFML/Graphics.hpp>

class Bullet : public sf::Drawable, public sf::Transformable
{
public:
	Bullet(const sf::Vector2f &pos, float degrees);
	sf::Vector2f &getVelocity()
	{
		return velocity;
	}
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	sf::Vector2f velocity;
	sf::RectangleShape line;
};
#endif