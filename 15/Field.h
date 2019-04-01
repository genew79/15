#pragma once
#include <SFML/Graphics.hpp>
#include "Element.h"

class Field : public sf::Drawable, public sf::Transformable
{
protected:
	std::vector<Element> elements;
public:
	Field();
	~Field();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Vector2i GetEmptyPos();
};
