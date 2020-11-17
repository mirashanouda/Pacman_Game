#include "Fruit.h"

Fruit::Fruit()
{
	objectRow = 21;
	objectColumn = 0;
	object.setPosition(float(50 + objectColumn * 40), float(50 + objectRow * 40));
	object.setSize(Vector2f(40, 40));
	t.loadFromFile("fruits.png");
	object.setTexture(&t);
}

void Fruit::randPosition(int board_arr[row][column])
{
	while (true)
	{
		objectColumn = rand() % 19;
		objectRow = rand() % 21;
		if (board_arr[objectRow][objectColumn] < 0)
			continue;
		else
			object.setPosition(float(50 + objectColumn * 40), float(50 + objectRow * 40));
		break;
	}
}

Fruit::~Fruit()
{
}
