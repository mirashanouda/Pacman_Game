#ifndef FRUIT
#define FRUIT
#include "MovingObject.h"

class Fruit: public MovingObject //Fruit class is inherited from MovingObject class as it has all the features of MovingObject

{
public:
	Fruit();
	void randPosition(int[row][column]);
	~Fruit();
};

#endif