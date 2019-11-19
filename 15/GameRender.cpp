#include "GameRender.h"
#include "Assets.h"

GameRender::GameRender(GameModel *game)
{
	m_game = game;
	Init();
}

GameRender::~GameRender()
{
}

bool GameRender::Init()
{
	setPosition(50.f, 50.f);
	// Создаем окно размером 600 на 600 и частотой обновления 60 кадров в секунду
	m_window.create(sf::VideoMode(600, 600), "15");
	m_window.setFramerateLimit(60);
	// Текст с обозначением клавиш
	m_text = sf::Text("F2 - New Game / Esc - Exit / Arrow Keys - Move Tile", Assets::Instance().font, 20);
	m_text.setFillColor(sf::Color::Cyan);
	m_text.setPosition(5.f, 5.f);
	return true;
}

void GameRender::Render()
{
	m_window.clear();
	m_window.draw(*this);
	m_window.draw(m_text);
	m_window.display();
}

void GameRender::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	sf::Color color = sf::Color(200, 100, 200);

	// Рисуем рамку игрового поля
	sf::RectangleShape shape(sf::Vector2f(GameModel::FIELD_SIZE, GameModel::FIELD_SIZE));
	shape.setOutlineThickness(2.f);
	shape.setOutlineColor(color);
	shape.setFillColor(sf::Color::Transparent);
	target.draw(shape, states);

	// Подготавливаем рамку для отрисовки всех плашек
	shape.setSize(sf::Vector2f(GameModel::CELL_SIZE - 2, GameModel::CELL_SIZE - 2));
	shape.setOutlineThickness(2.f);
	shape.setOutlineColor(color);
	shape.setFillColor(sf::Color::Transparent);

	// Подготавливаем текстовую заготовку для отрисовки номеров плашек
	sf::Text text("", Assets::Instance().font, 52);

	int *elements = m_game->Elements();
	for (unsigned int i = 0; i < GameModel::ARRAY_SIZE; i++)
	{
		shape.setOutlineColor(color);
		text.setFillColor(color);
		text.setString(std::to_string(elements[i]));
		if (m_game->IsSolved())
		{
			// Решенную головоломку выделяем другим цветом
			shape.setOutlineColor(sf::Color::Cyan);
			text.setFillColor(sf::Color::Cyan);
		}
		else if (elements[i] == i + 1)
		{
			// Номера плашек на своих местах выделяем цветом
			text.setFillColor(sf::Color::Green);
		}

		// Рисуем все плашки, кроме пустой
		if (elements[i] > 0)
		{
			// Вычисление позиции плашки для отрисовки
			sf::Vector2f position(i % GameModel::SIZE * GameModel::CELL_SIZE + 10.f, i / GameModel::SIZE * GameModel::CELL_SIZE + 10.f);
			shape.setPosition(position);
			// Позицию текста подбирал вручную
			text.setPosition(position.x + 30.f + (elements[i] < 10 ? 15.f : 0.f), position.y + 25.f);
			target.draw(shape, states);
			target.draw(text, states);
		}
	}
}
