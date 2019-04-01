#include "Assets.h"
#include "Element.h"

Element::Element(int val)
{
	value = val;
	color = sf::Color(200, 100, 200);
}

Element::~Element()
{
}

void Element::SetPosition(sf::Vector2f pos)
{
	position = pos;
}

void Element::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (value > 0)
	{
		sf::RectangleShape shape(sf::Vector2f(118.f, 118.f));
		states.transform *= getTransform();
		shape.setPosition(position);
		shape.setOutlineThickness(2.f);
		shape.setOutlineColor(color);
		shape.setFillColor(sf::Color::Transparent);
		target.draw(shape, states);

		sf::Text text;
		text.setFont(Assets::Instance().font);
		text.setString(std::to_string(value));
		text.setCharacterSize(52);
		text.setFillColor(color);
		text.setPosition(position.x + 30.f + (value < 10 ? 15.f : 0.f), position.y + 25.f);
		target.draw(text, states);
	}
}
