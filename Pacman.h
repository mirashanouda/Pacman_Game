#ifndef PACMAN
#define PACMAN
#include "MovingObject.h"
#include "Ghost.h"
#include "Fruit.h"

class Ghost;
class Pacman: public MovingObject //Pacman class is inherited from MovingObject class as it has all the features of MovingObject 
{
private:
	int pellets;
	Sound dot;
	Sound eatGhost;
	Sound death;
	Sound fruit;

	SoundBuffer d;
	SoundBuffer e;
	SoundBuffer dth;
	SoundBuffer f;
	/*Music dot;
	Music eatGhost;
	Music death;
	Music fruit;*/
public:
	Pacman(); //Default Constructor
	int getPellets() const;
	void moving(Event E, int [row][column]); //move pacman on window
	bool removeDot(RectangleShape[row][column],int[row][column], Texture&, Texture&, int&, Fruit&); //eat pellets
	void faceGhost(Ghost &g1, Ghost& g2, Ghost &g3, int & live_count);
	void resetGhostPosition(Ghost&, Ghost&, Ghost&);
	~Pacman(); //Destructor
};

#endif