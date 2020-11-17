#include "Ghost.h"

Ghost::Ghost(int c, string fileName)
{
	objectRow = 9;
	objectColumn = 7 + c;
	object.setPosition(float(50 + objectColumn * 40), float(50 + objectRow * 40));
	object.setSize(Vector2f(40, 40));
	t.loadFromFile(fileName);
	object.setTexture(&t);
}

void Ghost::ghostMoving(int board[row][column], int next)
{
	if (next == 93)//right portal
	{
		objectColumn = 0;
		object.setPosition(float(50 + objectColumn * 40), float(50 + objectRow * 40));
	}
	else if (next == 77)//left portal
	{
		objectColumn = 18;
		object.setPosition(float(50 + objectColumn * 40), float(50 + objectRow * 40));
	}
	else if (next == board[objectRow][objectColumn] + 1)//move right
	{
		object.move(40, 0);
		objectColumn++;
	}
	else if (next == board[objectRow][objectColumn] - 1)//move left
	{
		object.move(-40, 0);
		objectColumn--;
	}
	else if (next < board[objectRow][objectColumn] - 1 && board[objectRow][objectColumn] - 1 >= 0)//move up
	{
		objectRow--;
		object.move(0, -40);
	}
	else if (next > board[objectRow][objectColumn] + 1 && board[objectRow][objectColumn] + 1 >= 0)//move down
	{
		objectRow++;
		object.move(0, 40);
	}
}

//Finding the shortest path
vector<vector<int>> Ghost::Dijkstra(int Graph[matrix][matrix], int startNode)
{
	int costs[matrix], previous[matrix];
	bool visited[matrix];

	//costs, previous, and visited
	for (int i = 0; i < matrix; i++)
	{
		costs[i] = Graph[startNode][i];
		previous[i] = startNode;
		visited[i] = false;
	}
	// startNode
	costs[startNode] = 0;
	visited[startNode] = true;

	//contianue 1st node as I already visited the startNode:
	int count = 1, nextNode, minimumCost;
	while (count < matrix)
	{
		// Find the minimum cost in order to visit its node in the next step.
		minimumCost = infinity;//999, I put it here to initialize the min each time i go to next node
		for (int i = 0; i < matrix; i++)
			if ((costs[i] < minimumCost) && (visited[i] == false))
			{
				minimumCost = costs[i];
				nextNode = i;
			}

		// Visit the node.
		visited[nextNode] = true;
		// Update the costs of the children of the visited node.
		for (int i = 0; i < matrix; i++)
			if ((minimumCost + Graph[nextNode][i] < costs[i]) && (visited[i] == false))
			{
				costs[i] = minimumCost + Graph[nextNode][i];
				previous[i] = nextNode;
			}
		count++;
	}
	// Fill the paths.
	int j;
	vector<vector<int>> paths;
	paths.resize(matrix);
	for (int i = 0; i < matrix; i++)
	{
		paths[i].push_back(i);
		if (i != startNode)
		{
			j = i;
			do
			{
				j = previous[j];
				paths[i].push_back(j);
			} while (j != startNode);
		}
	}
	return paths;
}

Ghost::~Ghost()
{
}
