#include "Pacman.h"

Pacman::Pacman()
{
	objectRow = 15;
	objectColumn = 9;
	object.setPosition(float(50 + objectColumn * 40),float( 50 + objectRow * 40)); 
	object.setSize(Vector2f(40, 40));
	t.loadFromFile("pac.png");
	object.setTexture(&t);
	pellets = 0;

	d.loadFromFile("pellet.wav");
	e.loadFromFile("pacman_eatghost.wav");
	dth.loadFromFile("death.wav");
	f.loadFromFile("pacman_eatfruit.wav");


	dot.setBuffer(d);
	eatGhost.setBuffer(e);
	death.setBuffer(dth);
	fruit.setBuffer(f);

	/*dot.openFromFile("pellet.wav");
	eatGhost.openFromFile("pacman_eatghost.wav");
	death.openFromFile("death.wav");
	fruit.openFromFile("pacman_eatfruit.wav");*/
}

int Pacman::getPellets() const
{
	return pellets;
}

void Pacman::moving(Event E, int board[row][column])
{
	switch (E.key.code)
	{
	case Keyboard::Up:
		if (board[objectRow - 1][objectColumn] >= 0)
		{
			object.move(0, -40);
			objectRow--;
			this->portals();
		}
		break;

	case Keyboard::Down:
		if (board [objectRow + 1][objectColumn] >= 0)
		{
			object.move(0, 40);
			objectRow++;
			this->portals();
		}
		break;

	case Keyboard::Right:
		if (board[objectRow][objectColumn + 1] >= 0)
		{
			object.move(40, 0);
			objectColumn++;
			this->portals();
		}
		break;

	case Keyboard::Left:
		if (board[objectRow][objectColumn - 1] >= 0)
		{
			object.move(-40, 0);
			objectColumn--;
			this->portals();
		}
		break;
	}
}


bool Pacman::removeDot(RectangleShape arr[row][column],int borad_arr[row][column], Texture& dot, Texture& power, int& score, Fruit& f)
{
	if (object.getPosition() == f.getObjectPosition())
	{
		arr[objectRow][objectColumn].setFillColor(Color::Black);
		score = score + 100;
		fruit.play();
		f.randPosition(borad_arr);
	}
	if (arr[objectRow][objectColumn].getTexture() == (&dot) && arr[objectRow][objectColumn].getFillColor() != Color::Black)
	{
		arr[objectRow][objectColumn].setFillColor(Color::Black);
		score = score + 10;
		this->dot.play();
		pellets++;
	} 
	if (arr[objectRow][objectColumn].getTexture() == (&power) && arr[objectRow][objectColumn].getFillColor() != Color::Black)
	{
		arr[objectRow][objectColumn].setFillColor(Color::Black);
		score = score + 50;
		this->dot.play();
		pellets++;

		return true;//if faced a power pellet
	}
	return false;
}
void Pacman::faceGhost(Ghost &g1, Ghost &g2, Ghost &g3,int & live_count)
{
	//facing inky
	if (object.getPosition() == g1.getObjectPosition() ||
		object.getPosition() == g2.getObjectPosition() ||
		object.getPosition() == g3.getObjectPosition()) //OR: object.getGlobalBounds().intersects(g1.getObject().getGlobalBounds()
	{
		--live_count;
		death.play();
		//Pacman returns to its first position
		objectColumn = 9;
		objectRow = 15;
		object.setPosition(float(50 + objectColumn * 40), float(50 + objectRow * 40));

		//Ghost returns to its first position
		g1.setRow(9);
		g2.setRow(9);
		g3.setRow(9);

		g1.setColumn(8);
		g2.setColumn(9);
		g3.setColumn(10);

		g1.setObjectPosition(float(50 + g1.getColumn() * 40), float(50 + g1.getRow() * 40));
		g2.setObjectPosition(float(50 + g2.getColumn() * 40), float(50 + g2.getRow() * 40));
		g3.setObjectPosition(float(50 + g3.getColumn() * 40), float(50 + g3.getRow() * 40));
	}
}

void Pacman::resetGhostPosition(Ghost& g1, Ghost& g2, Ghost& g3)
{
	
	if (object.getPosition() == g1.getObjectPosition())
	{
		g1.setRow(9);
		g1.setColumn(8);
		g1.setObjectPosition(float(50 + g1.getColumn() * 40), float(50 + g1.getRow() * 40));
		eatGhost.play();
	}
	if (object.getPosition() == g2.getObjectPosition())
	{
		g2.setRow(9); 	
		g2.setColumn(9);
		g2.setObjectPosition(float(50 + g2.getColumn() * 40), float(50 + g2.getRow() * 40));
		eatGhost.play();
	}
	if (object.getPosition() == g3.getObjectPosition())
	{
		g3.setRow(9);
		g3.setColumn(10);
		g3.setObjectPosition(float(50 + g3.getColumn() * 40), float(50 + g3.getRow() * 40));
		eatGhost.play();
	}
}
Pacman::~Pacman()
{
}