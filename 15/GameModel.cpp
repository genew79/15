#include "GameModel.h"

GameModel::GameModel()
{
	// Подгружаем шрифт для отрисовки элементов
	Init();
}

void GameModel::Init()
{
	// Заполняем массив плашек
	for (int i = 0; i < ARRAY_SIZE - 1; i++) elements[i] = i + 1;
	// Ставим пустую плашку в правую нижнюю позицию
	empty_index = ARRAY_SIZE - 1;
	elements[empty_index] = 0;	// Пустая плашка имеет значение = 0
	solved = true;
}

bool GameModel::Check()
{
	// Проверка собранности головоломки
	for (unsigned int i = 0; i < ARRAY_SIZE; i++)
	{
		if (elements[i] > 0 && elements[i] != i + 1) return false;
	}
	return true;
}

void GameModel::Move(Direction direction)
{
	// Вычисляем строку и колонку пустой плашки
	int col = empty_index % SIZE;
	int row = empty_index / SIZE;

	// Проверка на возможность перемещения и вычисление индекса перемещаемой плашки
	int move_index = -1;
	if (direction == Direction::Left && col < (SIZE - 1)) move_index = empty_index + 1;
	if (direction == Direction::Right && col > 0) move_index = empty_index - 1;
	if (direction == Direction::Up && row < (SIZE - 1)) move_index = empty_index + SIZE;
	if (direction == Direction::Down && row > 0) move_index = empty_index - SIZE;

	// Перемещение плашки на место пустой
	if (empty_index >= 0 && move_index >= 0)
	{
		int tmp = elements[empty_index];
		elements[empty_index] = elements[move_index];
		elements[move_index] = tmp;
		empty_index = move_index;
	}
	solved = Check();
}
