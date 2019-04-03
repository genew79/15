#pragma once
#include <SFML/Graphics.hpp>

class Element : public sf::Drawable, public sf::Transformable
{
protected:
	int value;
	sf::Vector2f position;
	sf::Color color;
	sf::Color text_color;
public:
	Element(int val);
	~Element();
	void SetPosition(sf::Vector2f pos);
	void SetColor(sf::Color _color, sf::Color _text_color);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	int Value() const { return value; };
};

