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
	field.SetSize(sf::Vector2i(500, 500));
	field.setPosition(50.f, 50.f);

	sf::Event event;
	int counter = 100;

	std::vector<Direction> log;

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
					if (event.key.code == sf::Keyboard::Left && field.IsDirectionPossible(Direction::Left)) { log.push_back(Direction::Left); field.Move(Direction::Left); }
					if (event.key.code == sf::Keyboard::Right && field.IsDirectionPossible(Direction::Right)) { log.push_back(Direction::Right); field.Move(Direction::Right); }
					if (event.key.code == sf::Keyboard::Up && field.IsDirectionPossible(Direction::Up)) { log.push_back(Direction::Up); field.Move(Direction::Up); }
					if (event.key.code == sf::Keyboard::Down && field.IsDirectionPossible(Direction::Down)) { log.push_back(Direction::Down); field.Move(Direction::Down); }
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
			Direction dir = (Direction)(rand() % 4);
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
				Direction dir = log.back();
				if (dir == Direction::Left) field.Move(Direction::Right);
				if (dir == Direction::Right) field.Move(Direction::Left);
				if (dir == Direction::Up) field.Move(Direction::Down);
				if (dir == Direction::Down) field.Move(Direction::Up);
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
