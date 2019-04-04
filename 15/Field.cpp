#include "Field.h"

Field::Field()
{
	color = sf::Color(200, 100, 200);
	for (int i = 0; i < 15; i++)
	{
		Element elem(i + 1);
		elem.SetPosition(GetElementPosition(i));
		elements.push_back(elem);
	}
	Element elem(0);
	elem.SetPosition(GetElementPosition(15));
	elements.push_back(elem);
}

Field::~Field()
{
}

void Field::SetSize(sf::Vector2i sz)
{
	size = sz;
}

sf::Vector2f Field::GetElementPosition(int index)
{
	return sf::Vector2f(index % 4 * cell_size + 10.f, index / 4 * cell_size + 10.f);
}

int Field::GetElementIndex(sf::Vector2i position)
{
	if (position.x < (int)getPosition().x + 10) return -1;
	if (position.y < (int)getPosition().y + 10) return -1;
	if (position.x >= (int)getPosition().x + 10 + cell_size * 4) return -1;
	if (position.y >= (int)getPosition().y + 10 + cell_size * 4) return -1;
	return (position.y - (int)getPosition().y - 10) / cell_size * 4 + (position.x - (int)getPosition().x - 10) / cell_size;
}

void Field::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape shape(sf::Vector2f(1.f * size.x, 1.f * size.y));
	states.transform *= getTransform();
	shape.setOutlineThickness(2.f);
	shape.setOutlineColor(color);
	shape.setFillColor(sf::Color::Transparent);
	target.draw(shape, states);
	bool check = Check();
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		if(check) ((Element&)elements[i]).SetColor(sf::Color::Cyan, sf::Color::Cyan);
		else if (elements[i].Value() == i + 1)
		{
			((Element&)elements[i]).SetColor(sf::Color(200, 100, 200), sf::Color::Green);
		}
		else
		{
			((Element&)elements[i]).SetColor(sf::Color(200, 100, 200), sf::Color(200, 100, 200));
		}
		elements[i].draw(target, states);
	}
}

int Field::GetEmptyIndex() const
{
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		if (elements[i].Value() == 0) return i;
	}
	return -1;
}

void Field::Move(Direction direction)
{
	int move_index = -1;
	int empty_index = GetEmptyIndex();
	int col = empty_index % 4;
	int row = empty_index / 4;

	if (direction == Field::Left && col < 3) move_index = empty_index + 1;
	if (direction == Field::Right && col > 0) move_index = empty_index - 1;
	if (direction == Field::Up && row < 3) move_index = empty_index + 4;
	if (direction == Field::Down && row > 0) move_index = empty_index - 4;
	SwapElements(empty_index, move_index);
}

void Field::SwapElements(int index1, int index2)
{
	if (index1 >= 0 && index2 >= 0)
	{
		Element tmp = elements[index1];
		elements[index1] = elements[index2];
		elements[index2] = tmp;
		elements[index1].SetPosition(GetElementPosition(index1));
		elements[index2].SetPosition(GetElementPosition(index2));
	}
}

bool Field::Check() const
{
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		if (elements[i].Value() > 0 && elements[i].Value() != i + 1) return false;
	}
	return true;
}

bool Field::IsDirectionPossible(Field::Direction direction)
{
	int empty_index = GetEmptyIndex();
	int col = empty_index % 4;
	int row = empty_index / 4;
	return
		direction == Field::Left && col < 3 ||
		direction == Field::Right && col > 0 ||
		direction == Field::Up && row < 3 ||
		direction == Field::Down && row > 0;
}
