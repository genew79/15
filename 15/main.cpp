#include <SFML/Graphics.hpp>
#include "Assets.h"
#include "Field.h"

int main()
{
	Assets& assets = Assets::Instance();
	assets.Load();

	sf::VideoMode fullscreenMode = sf::VideoMode::getFullscreenModes()[0];

	//	sf::RenderWindow window(fullscreenMode, "SFML works!", sf::Style::Fullscreen);
	sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");

	window.setFramerateLimit(60);

	sf::Text text;
	text.setFont(assets.font);
	text.setString(std::to_string(fullscreenMode.width) + " x " + std::to_string(fullscreenMode.height));
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Red);
	text.setPosition(0.f, 0.f);

	sf::View view(sf::FloatRect(0.f, 0.f, 600.f, 600.f));

	float xpos = 50.f, ypos = 50.f;
	Field field;
	field.setPosition(xpos, ypos);
	field.SetSize(sf::Vector2i(500, 500));

	sf::Vector2i empty_pos;
	sf::Event event;
	int counter = 200;

	while (window.isOpen())
	{
		empty_pos = field.GetEmptyPos();

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
			{
				window.close();
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Left) field.Move(Field::Left);
				if (event.key.code == sf::Keyboard::Right) field.Move(Field::Right);
				if (event.key.code == sf::Keyboard::Up) field.Move(Field::Up);
				if (event.key.code == sf::Keyboard::Down) field.Move(Field::Down);
			}

			if (event.type == sf::Event::MouseMoved)
			{
				sf::Vector2i position = sf::Mouse::getPosition(window);
				text.setString("Mouse pos: " + std::to_string(position.x) + ", " + std::to_string(position.y));
				field.MouseMove(position);
			}

			if (event.type == sf::Event::Resized)
			{
				// update the view to the new size of the window
				sf::FloatRect visibleArea(0.f, 0.f, 1.0f * event.size.width, 1.0f * event.size.height);
				window.setView(sf::View(visibleArea));
			}
		}

		if (counter > 0)
		{
			Field::Direction dir = (Field::Direction)(rand() % 4);
			field.Move(dir);
			counter--;
		}

		window.clear();
		window.draw(field);
		window.draw(text);
		window.display();
	}

	return 0;
}
