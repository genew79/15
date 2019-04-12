#include <SFML/Graphics.hpp>
#include "Field.h"

int main()
{
	// ������� ���� �������� 600 �� 600 � �������� ���������� 60 ������ � �������
	sf::RenderWindow window(sf::VideoMode(600, 600), "15");
	window.setFramerateLimit(60);

	sf::Font font;
	font.loadFromFile("calibri.ttf");

	// ����� � ������������ ������
	sf::Text text("F2 - New Game / Esc - Exit / Arrow Keys - Move Tile", font, 20);
	text.setFillColor(sf::Color::Cyan);
	text.setPosition(5.f, 5.f);

	// ������� ������ ����
	Field field;
	field.setPosition(50.f, 50.f);

	sf::Event event;
	int move_counter = 0;	// ������� ��������� ����� ��� ������������� �����������

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				// �������� ������� ������� - ��������� ��������������� ��������
				if (event.key.code == sf::Keyboard::Escape) window.close();
				if (event.key.code == sf::Keyboard::Left) field.Move(Direction::Left);
				if (event.key.code == sf::Keyboard::Right) field.Move(Direction::Right);
				if (event.key.code == sf::Keyboard::Up) field.Move(Direction::Up);
				if (event.key.code == sf::Keyboard::Down) field.Move(Direction::Down);
				// ����� ����
				if (event.key.code == sf::Keyboard::F2)
				{
					field.Init();
					move_counter = 100;
				}
			}
		}

		// ���� ������� ����� ������ ����, ���������� ������������ �����������
		if (move_counter-- > 0) field.Move((Direction)(rand() % 4));

		// ��������� ����������� �������� �� ���������
		window.clear();
		window.draw(field);
		window.draw(text);
		window.display();
	}

	return 0;
}
