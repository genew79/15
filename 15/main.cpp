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

	Field field;

	float xpos = 50.f, ypos = 50.f;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
			{
				window.close();
			}
			if (event.type == sf::Event::Resized)
			{
				// update the view to the new size of the window
				sf::FloatRect visibleArea(0.f, 0.f, 1.0f * event.size.width, 1.0f * event.size.height);
				window.setView(sf::View(visibleArea));
			}
		}
		window.clear();
		field.setPosition(xpos, ypos);
		window.draw(field);
		window.draw(text);
		window.display();
	}

	return 0;
}
