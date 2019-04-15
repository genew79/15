#pragma once
#include <SFML/Graphics.hpp>

const int SIZE = 4;
const int ARRAY_SIZE = SIZE * SIZE;
const int FIELD_SIZE = 500;
const int CELL_SIZE = 120;
enum class Direction { Left = 0, Right = 1, Up = 2, Down = 3 };

class Game : public sf::Drawable, public sf::Transformable
{
protected:
	int elements[ARRAY_SIZE];
	sf::Font font;
	int empty_index;
public:
	Game();
	~Game() {};
	void Init();
	sf::Vector2f GetElementPosition(int index) const;
	void Move(Direction direction);
	bool Check() const;
public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
