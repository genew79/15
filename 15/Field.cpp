#include "Assets.h"
#include "Field.h"

Field::Field()
{
	for (int i = 0; i < FIELD_SIZE - 1; i++) elements[i] = i + 1;
	elements[FIELD_SIZE - 1] = 0;
}

Field::~Field()
{
}

sf::Vector2f Field::GetElementPosition(int index) const
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
	sf::Color color = sf::Color(200, 100, 200);

	sf::RectangleShape shape(sf::Vector2f(1.f * size.x, 1.f * size.y));
	states.transform *= getTransform();
	shape.setOutlineThickness(2.f);
	shape.setOutlineColor(color);
	shape.setFillColor(sf::Color::Transparent);
	target.draw(shape, states);

	shape.setSize(sf::Vector2f(118.f, 118.f));
	shape.setOutlineThickness(2.f);
	shape.setOutlineColor(color);
	shape.setFillColor(sf::Color::Transparent);

	sf::Text text;
	text.setFont(Assets::Instance().font);
	text.setCharacterSize(52);
	text.setFillColor(color);

	bool check = Check();
	for (unsigned int i = 0; i < FIELD_SIZE; i++)
	{
		shape.setOutlineColor(color);
		text.setFillColor(color);
		text.setString(std::to_string(elements[i]));
		if (check)
		{
			shape.setOutlineColor(sf::Color::Cyan);
			text.setFillColor(sf::Color::Cyan);
		}
		else if (elements[i] == i + 1)
		{
			text.setFillColor(sf::Color::Green);
		}

		if (elements[i] > 0)
		{
			sf::Vector2f position = GetElementPosition(i);
			shape.setPosition(position);
			target.draw(shape, states);
			text.setPosition(position.x + 30.f + (elements[i] < 10 ? 15.f : 0.f), position.y + 25.f);
			target.draw(text, states);
		}
	}
}

int Field::GetEmptyIndex() const
{
	for (unsigned int i = 0; i < FIELD_SIZE; i++)
	{
		if (elements[i] == 0) return i;
	}
	return -1;
}

void Field::Move(Direction direction)
{
	int move_index = -1;
	int empty_index = GetEmptyIndex();
	int col = empty_index % 4;
	int row = empty_index / 4;

	if (direction == Direction::Left && col < 3) move_index = empty_index + 1;
	if (direction == Direction::Right && col > 0) move_index = empty_index - 1;
	if (direction == Direction::Up && row < 3) move_index = empty_index + 4;
	if (direction == Direction::Down && row > 0) move_index = empty_index - 4;
	SwapElements(empty_index, move_index);
}

void Field::SwapElements(int index1, int index2)
{
	if (index1 >= 0 && index2 >= 0)
	{
		int tmp = elements[index1];
		elements[index1] = elements[index2];
		elements[index2] = tmp;
	}
}

bool Field::Check() const
{
	for (unsigned int i = 0; i < FIELD_SIZE; i++)
	{
		if (elements[i] > 0 && elements[i] != i + 1) return false;
	}
	return true;
}

bool Field::IsDirectionPossible(Direction direction)
{
	int empty_index = GetEmptyIndex();
	int col = empty_index % 4;
	int row = empty_index / 4;
	return
		direction == Direction::Left && col < 3 ||
		direction == Direction::Right && col > 0 ||
		direction == Direction::Up && row < 3 ||
		direction == Direction::Down && row > 0;
}
