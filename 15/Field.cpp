#include "Field.h"

Field::Field()
{
	font.loadFromFile("calibri.ttf");
	Init();
}

void Field::Init()
{
	// ��������� ������ ������
	for (int i = 0; i < FIELD_SIZE - 1; i++) elements[i] = i + 1;
	elements[FIELD_SIZE - 1] = 0;	// ������ ������ ����� �������� = 0
}

int Field::GetEmptyIndex() const
{
	// ���� ������ ������ ������
	for (unsigned int i = 0; i < FIELD_SIZE; i++) if (elements[i] == 0) return i;
	return -1;
}

sf::Vector2f Field::GetElementPosition(int index) const
{
	// ���������� ������� ������ ��� ���������
	return sf::Vector2f(index % SIZE * 120.f + 10.f, index / SIZE * 120.f + 10.f);
}

void Field::Move(Direction direction)
{
	// ����������� ������
	int move_index = -1;
	// ��������� ������ � ������� ������ ������
	int empty_index = GetEmptyIndex();
	int col = empty_index % SIZE;
	int row = empty_index / SIZE;

	// �������� �� ����������� ����������� � ���������� ������� ������������ ������
	if (direction == Direction::Left && col < (SIZE - 1)) move_index = empty_index + 1;
	if (direction == Direction::Right && col > 0) move_index = empty_index - 1;
	if (direction == Direction::Up && row < (SIZE - 1)) move_index = empty_index + SIZE;
	if (direction == Direction::Down && row > 0) move_index = empty_index - SIZE;

	// ����������� ������ �� ����� ������
	if (empty_index >= 0 && move_index >= 0)
	{
		int tmp = elements[empty_index];
		elements[empty_index] = elements[move_index];
		elements[move_index] = tmp;
	}
}

bool Field::Check() const
{
	// �������� ����������� �����������
	for (unsigned int i = 0; i < FIELD_SIZE; i++) if (elements[i] > 0 && elements[i] != i + 1) return false;
	return true;
}

void Field::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Color color = sf::Color(200, 100, 200);

	// ������ ����� �������� ����
	sf::RectangleShape shape(sf::Vector2f(500.f, 500.f));
	states.transform *= getTransform();
	shape.setOutlineThickness(2.f);
	shape.setOutlineColor(color);
	shape.setFillColor(sf::Color::Transparent);
	target.draw(shape, states);

	// �������������� ����� ��� ��������� ���� ������
	shape.setSize(sf::Vector2f(118.f, 118.f));
	shape.setOutlineThickness(2.f);
	shape.setOutlineColor(color);
	shape.setFillColor(sf::Color::Transparent);

	// �������������� ��������� ��������� ��� ��������� ������� ������
	sf::Text text("", font, 52);

	bool check = Check();	// �������� �� ��, ��� ��� ������ �� ����� ������
	for (unsigned int i = 0; i < FIELD_SIZE; i++)
	{
		shape.setOutlineColor(color);
		text.setFillColor(color);
		text.setString(std::to_string(elements[i]));
		if (check)
		{
			// �������� ����������� �������� ������ ������
			shape.setOutlineColor(sf::Color::Cyan);
			text.setFillColor(sf::Color::Cyan);
		}
		else if (elements[i] == i + 1)
		{
			text.setFillColor(sf::Color::Green);	// ������ ������ �� ����� ������ �������� ������
		}

		// ������ ��� ������, ����� ������
		if (elements[i] > 0)
		{
			sf::Vector2f position = GetElementPosition(i);
			shape.setPosition(position);
			text.setPosition(position.x + 30.f + (elements[i] < 10 ? 15.f : 0.f), position.y + 25.f);	// ������� ������ �������� �������
			target.draw(shape, states);
			target.draw(text, states);
		}
	}
}
