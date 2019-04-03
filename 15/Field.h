#pragma once
#include <SFML/Graphics.hpp>
#include "Element.h"

class Field : public sf::Drawable, public sf::Transformable
{
protected:
	sf::Vector2i size;
	int cell_size = 120;
	std::vector<Element> elements;
	sf::Color color;
public:
	enum Direction { Left = 0, Right = 1, Up = 2, Down = 3 };
public:
	Field();
	~Field();
	void SetSize(sf::Vector2i sz);
	sf::Vector2f GetElementPosition(int index);
	int GetElementIndex(sf::Vector2i position);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	int GetEmptyIndex() const;
	void Move(Direction direction);
	void SwapElements(int index1, int index2);
	bool Check() const;
	void MouseMove(sf::Vector2i pos);
	std::vector<int> GetSwapIndexes();
	bool IsDirectionPossible(Field::Direction dir);
};
