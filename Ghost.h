#ifndef GHOST
#define GHOST
#include "MovingObject.h"

class Ghost: public MovingObject
{
public:
	Ghost(int c, string fileName);
	void ghostMoving(int[row][column], int);
	vector<vector<int>> Dijkstra(int graph[matrix][matrix], int startNode);
	~Ghost();
};

#endif