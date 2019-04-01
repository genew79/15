#pragma once
#include <SFML/Graphics.hpp>
#include "Element.h"

class Field : public sf::Drawable, public sf::Transformable
{
protected:
	sf::Vector2i size;
	std::vector<Element> elements;
	sf::Color color;
public:
	enum Direction { Left = 0, Right = 1, Up = 2, Down = 3 };
public:
	Field();
	~Field();
	void SetSize(sf::Vector2i sz) { size = sz; };
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Vector2i GetEmptyPos();
	void Move(Direction direction);
	void SwapElements(int index1, int index2);
	void MouseMove(sf::Vector2i pos);
};
