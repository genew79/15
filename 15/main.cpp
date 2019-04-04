#include <SFML/Graphics.hpp>
#include "Assets.h"
#include "Field.h"

int main()
{
	Assets& assets = Assets::Instance();
	assets.Load();

	sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
	window.setFramerateLimit(60);

	sf::Text text;
	text.setFont(assets.font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Red);
	text.setPosition(0.f, 0.f);

	Field field;
	field.SetSize(sf::Vector2i(500, 500));
	field.setPosition(50.f, 50.f);

	sf::Event event;
	int counter = 100;

	std::vector<Field::Direction> log;

	bool mode_solve = false;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
			{
				window.close();
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (!mode_solve)
				{
					if (event.key.code == sf::Keyboard::R && log.size() > 0) mode_solve = true;
					if (event.key.code == sf::Keyboard::R && log.size() == 0) counter = 100;
					if (event.key.code == sf::Keyboard::Left && field.IsDirectionPossible(Field::Left)) { log.push_back(Field::Left); field.Move(Field::Left); }
					if (event.key.code == sf::Keyboard::Right && field.IsDirectionPossible(Field::Right)) { log.push_back(Field::Right); field.Move(Field::Right); }
					if (event.key.code == sf::Keyboard::Up && field.IsDirectionPossible(Field::Up)) { log.push_back(Field::Up); field.Move(Field::Up); }
					if (event.key.code == sf::Keyboard::Down && field.IsDirectionPossible(Field::Down)) { log.push_back(Field::Down); field.Move(Field::Down); }
				}
			}

			if (event.type == sf::Event::MouseMoved)
			{
				sf::Vector2i position = sf::Mouse::getPosition(window);
				std::string str;
				str = "Mouse pos: " + std::to_string(position.x) + ", " + std::to_string(position.y);
				str += "\n Cell index: " + std::to_string(field.GetElementIndex(position));
				text.setString(str);
			}
			if (event.type == sf::Event::MouseLeft)
			{
				sf::Vector2i position = sf::Mouse::getPosition(window);
				int index = field.GetElementIndex(position);
			}

			if (event.type == sf::Event::Resized)
			{
				// update the view to the new size of the window
				sf::FloatRect visibleArea(0.f, 0.f, 1.0f * event.size.width, 1.0f * event.size.height);
			}
		}

		if (counter > 0)
		{
			Field::Direction dir = (Field::Direction)(rand() % 4);
			if (field.IsDirectionPossible(dir))
			{
				log.push_back(dir);
				field.Move(dir);
			}
			counter--;
		}
		else if (mode_solve)
		{
			if (log.size() > 0)
			{
				Field::Direction dir = log.back();
				if (dir == Field::Left) field.Move(Field::Right);
				if (dir == Field::Right) field.Move(Field::Left);
				if (dir == Field::Up) field.Move(Field::Down);
				if (dir == Field::Down) field.Move(Field::Up);
				log.pop_back();
			}
			else mode_solve = false;
		}

		window.clear();
		window.draw(field);
		window.draw(text);
		window.display();
	}

	return 0;
}
