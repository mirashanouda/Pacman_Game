#include "MovingObject.h"

void MovingObject::setRow(int objectRow)
{
	this->objectRow = objectRow;
}

void MovingObject::setColumn(int objectColumn)
{
	this->objectColumn = objectColumn;
}

int MovingObject::getRow() const
{
	return objectRow;
}

int MovingObject::getColumn() const
{
	return objectColumn;
}

int MovingObject::onBoard(int board_arr[row][column]) const
{
	return board_arr[objectRow][objectColumn];
}

const Vector2f& MovingObject::getObjectPosition()
{
	return object.getPosition();
}

void MovingObject::setObjectPosition(float x, float y)
{
	object.setPosition(x, y);
}

void MovingObject::portals()
{
	if (object.getPosition() == Vector2f(50 + 18 * 40, 50 + 9 * 40)) //objectRow == 9 && objectColumn == 18
	{
		objectColumn = 0;
		object.setPosition(float(50 + objectColumn * 40), float(50 + objectRow * 40));
	}
	else if (object.getPosition() == Vector2f(50 + 0 * 40, 50 + 9 * 40))
	{
		objectColumn = 18;
		object.setPosition(float(50 + objectColumn * 40), float(50 + objectRow * 40));
	}
}

RectangleShape MovingObject::getObject() const
{
	return object;
}
