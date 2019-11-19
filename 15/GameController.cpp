#include "GameController.h"

GameController::GameController(GameModel *game, GameRender *render)
{
	m_game = game;
	m_render = render;
}

GameController::~GameController()
{
}

void GameController::Run()
{
	sf::Event event;
	int move_counter = 0;	// Счетчик случайных ходов для перемешивания головоломки

	while (m_render->window().isOpen())
	{
		while (m_render->window().pollEvent(event))
		{
			if (event.type == sf::Event::Closed) m_render->window().close();
			if (event.type == sf::Event::KeyPressed)
			{
				// Получаем нажатую клавишу - выполняем соответствующее действие
				if (event.key.code == sf::Keyboard::Escape) m_render->window().close();
				if (event.key.code == sf::Keyboard::Left) m_game->Move(Direction::Left);
				if (event.key.code == sf::Keyboard::Right) m_game->Move(Direction::Right);
				if (event.key.code == sf::Keyboard::Up) m_game->Move(Direction::Up);
				if (event.key.code == sf::Keyboard::Down) m_game->Move(Direction::Down);
				// Новая игра
				if (event.key.code == sf::Keyboard::F2)
				{
					m_game->Init();
					move_counter = 100;
				}
			}
		}

		// Если счетчик ходов больше нуля, продолжаем перемешивать головоломку
		if (move_counter-- > 0) m_game->Move((Direction)(rand() % 4));

		// Выполняем необходимые действия по отрисовке
		m_render->Render();
	}
}
