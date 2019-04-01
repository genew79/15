#pragma once
#include <SFML/Graphics.hpp>

class Element : public sf::Drawable, public sf::Transformable
{
protected:
	int value;
	sf::Vector2f position;
	sf::Color color;
public:
	Element(int val);
	~Element();
	void SetPosition(sf::Vector2f pos);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	int Value() { return value; };
};

