#ifndef MOVINGOBJECT
#define  MOVINGOBJECT

#include "Header.h"
class MovingObject
{
protected:
	RectangleShape object;
	Texture t;
	int objectRow;
	int objectColumn;
public:
	void setRow(int);
	void setColumn(int);
	int getRow() const;
	int getColumn() const;
	int onBoard(int[row][column]) const;
	const Vector2f& getObjectPosition();
	void setObjectPosition(float x, float y);
	void portals();
	RectangleShape getObject() const;
};
#endif