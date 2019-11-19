#pragma once
#include <SFML/Graphics.hpp>
#include "GameModel.h"

class GameRender : public sf::Drawable, public sf::Transformable
{
	GameModel *m_game;
	sf::RenderWindow m_window;
	sf::Text m_text;
public:
	GameRender(GameModel *game);
	~GameRender();
	sf::RenderWindow& window() { return m_window; };
	bool Init();
	void Render();
public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
