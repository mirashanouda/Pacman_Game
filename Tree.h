#include "Header.h"

struct Node
{
	int value;
	int height;
	Node* left;
	Node* right;
};
class Tree
{
private:
	//private attributes
	Node* root;
	vector<int> order;
	
	//private function
	Node* insert(Node* n, int v);
	void inOrder(Node* n);
	Node* createNode(int v);
	Node* rotateLeft(Node*);
	Node* rotateRight(Node*);
	int getHeight(Node* n);//we need it as it's used in the balancing 
	int getBalanceFactor(Node* n);


public:
	Tree();
	void userInsert(int);
	vector<int> getOrder();
	~Tree();
};

