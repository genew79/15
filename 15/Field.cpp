#include "Field.h"

Field::Field()
{
	for (int i = 1; i < 16; i++)
	{
		Element elem(i);
		elements.push_back(elem);
	}
}

Field::~Field()
{
}

void Field::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape shape(sf::Vector2f(500.f, 500.f));
	states.transform *= getTransform();
	shape.setOutlineThickness(2.f);
	shape.setOutlineColor(sf::Color(200, 200, 200));
	shape.setFillColor(sf::Color::Transparent);
	target.draw(shape, states);

	shape.setSize(sf::Vector2f(120.f, 120.f));
	shape.setOutlineThickness(2.f);
	shape.setOutlineColor(sf::Color(200, 200, 200));
	shape.setFillColor(sf::Color::Transparent);
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			shape.setPosition(x * 120.f + 10.f, y * 120.f + 10.f);
			if(x != rand() % 4 || y != rand() % 4) target.draw(shape, states);
		}
	}
}
