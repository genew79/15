#pragma once
#include <SFML/Graphics.hpp>

class Field : public sf::Drawable, public sf::Transformable
{
public:
	Field();
	~Field();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
