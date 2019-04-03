#include <iostream>
#include <conio.h>

int arr[16];

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

void step(int dir)
{
	int zero = get_zero();
	for (int i = 0; i < 4; i++) step(i);
}

void solve()
{

}

int main()
{
	init();
	show();

	solve();

	_getch();
	return 0;
}
