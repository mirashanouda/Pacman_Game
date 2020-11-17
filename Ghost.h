#ifndef GHOST
#define GHOST
#include "MovingObject.h"

class Ghost: public MovingObject //Ghost class is inherited from MovingObject class as it has all the features of MovingObject
{
public:
	Ghost(int c, string fileName);
	void ghostMoving(int[row][column], int);
	vector<vector<int>> Dijkstra(int graph[matrix][matrix], int startNode);
	~Ghost();
};

#endif