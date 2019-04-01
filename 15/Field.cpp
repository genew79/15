#include "Field.h"

Field::Field()
{
	for (int i = 0; i < 16; i++)
	{
		Element elem(i);
		elem.SetPosition(sf::Vector2f(i % 4 * 120.f + 10.f, i / 4 * 120.f + 10.f));
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
	shape.setOutlineColor(sf::Color(200, 100, 200));
	shape.setFillColor(sf::Color::Transparent);
	target.draw(shape, states);
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		elements[i].draw(target, states);
	}
}

sf::Vector2i Field::GetEmptyPos()
{
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		if (elements[i].Value() == 0) return sf::Vector2i(i % 4, i / 4);
	}
	return sf::Vector2i(-1, -1);
}
