#include "Field.h"

Field::Field()
{
	color = sf::Color(200, 100, 200);
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
	sf::RectangleShape shape(sf::Vector2f(1.f * size.x, 1.f * size.y));
	states.transform *= getTransform();
	shape.setOutlineThickness(2.f);
	shape.setOutlineColor(color);
	shape.setFillColor(sf::Color::Transparent);
	target.draw(shape, states);
	for (unsigned int i = 0; i < elements.size(); i++) elements[i].draw(target, states);
}

sf::Vector2i Field::GetEmptyPos()
{
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		if (elements[i].Value() == 0) return sf::Vector2i(i % 4, i / 4);
	}
	return sf::Vector2i(-1, -1);
}

void Field::Move(Direction direction)
{
	int move_index = -1;
	sf::Vector2i empty_pos = GetEmptyPos();
	int empty_index = empty_pos.y * 4 + empty_pos.x;

	if (direction == Field::Left && empty_pos.x < 3) move_index = empty_index + 1;
	if (direction == Field::Right && empty_pos.x > 0) move_index = empty_index - 1;
	if (direction == Field::Up && empty_pos.y < 3) move_index = empty_index + 4;
	if (direction == Field::Down && empty_pos.y > 0) move_index = empty_index - 4;
	SwapElements(empty_index, move_index);
}

void Field::SwapElements(int index1, int index2)
{
	if (index1 >= 0 && index2 >= 0)
	{
		Element tmp = elements[index1];
		elements[index1] = elements[index2];
		elements[index2] = tmp;
		elements[index1].SetPosition(sf::Vector2f(index1 % 4 * 120.f + 10.f, index1 / 4 * 120.f + 10.f));
		elements[index2].SetPosition(sf::Vector2f(index2 % 4 * 120.f + 10.f, index2 / 4 * 120.f + 10.f));
	}
}

void Field::MouseMove(sf::Vector2i pos)
{

}
