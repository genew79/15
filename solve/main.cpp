#include <iostream>
#include <conio.h>
#include <vector>

enum class Direction { Left = 0, Right = 1, Up = 2, Down = 3 };

int arr[16];

std::vector<Direction> stack;

void swap(int i1, int i2)
{
	int t = arr[i1];
	arr[i1] = arr[i2];
	arr[i2] = t;
}

void init()
{
	for (int i = 0; i < 16; i++) arr[i] = i;
	for (int k = 0; k < 1000; k++) swap(rand() % 16, rand() % 16);
}

void show()
{
	for (int i = 0; i < 16; i++) std::cout << arr[i] << " ";
	std::cout << std::endl;
}

int get_zero()
{
	for (int i = 0; i < 16; i++) if (arr[i] == 0) return i;
	return -1;
}

bool is_move_valid(Direction direction)
{
	int zero = get_zero();
	int col = zero % 4;
	int row = zero / 4;
	return
		direction == Direction::Left && col < 3 ||
		direction == Direction::Right && col > 0 ||
		direction == Direction::Up && row < 3 ||
		direction == Direction::Down && row > 0;
}

void move(Direction direction)
{
	int index = -1;
	int zero = get_zero();
	int col = zero % 4;
	int row = zero / 4;
	if (direction == Direction::Left && col < 3) index = zero + 1;
	if (direction == Direction::Right && col > 0) index = zero - 1;
	if (direction == Direction::Up && row < 3) index = zero + 4;
	if (direction == Direction::Down && row > 0) index = zero - 4;
	swap(zero, index);
}

void step()
{
	int zero = get_zero();
	if (is_move_valid(Direction::Right))
	{
		stack.push_back(Direction::Right);
		move(Direction::Right);
		step();
	}
}

int main()
{
	init();
	show();
	step();
	std::cout << "Stack size: " << stack.size() << std::endl;
	show();
	_getch();
	return 0;
}
