#include <SFML/Graphics.hpp>
#include "Assets.h"
#include "Field.h"

int main()
{
	Assets& assets = Assets::Instance();
	assets.Load();

	sf::RenderWindow window(sf::VideoMode(600, 600), "15");
	window.setFramerateLimit(60);

	sf::Text text;
	text.setFont(assets.font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Red);
	text.setPosition(0.f, 0.f);

	Field field;
	field.SetSize(sf::Vector2i(200, 200));
	field.setPosition(50.f, 50.f);

	sf::Event event;
	int counter = 100;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Left) field.Move(Direction::Left);
				if (event.key.code == sf::Keyboard::Right) field.Move(Direction::Right);
				if (event.key.code == sf::Keyboard::Up) field.Move(Direction::Up);
				if (event.key.code == sf::Keyboard::Down) field.Move(Direction::Down);
			}
		}

		if (counter > 0)
		{
			Direction dir = (Direction)(rand() % 4);
			if (field.IsDirectionPossible(dir)) field.Move(dir);
			counter--;
		}

		window.clear();
		window.draw(field);
		window.draw(text);
		window.display();
	}

	return 0;
}
