#include "Tree.h"
//it's AVL to make the search complixity always O(log N) not O(N) in the worest case scenarios 
Tree::Tree(){
	root = NULL;
}
Node* Tree::createNode(int v) {
	Node* n = new Node;
	n->value = v;
	n->left = NULL;
	n->right = NULL;
	n->height = 1;

	return n;
}

Node* Tree::insert(Node* r, int v) {

	//when does it return? 
	// 1. when this passed node is not a root for a tree.
	// 2. when the given value is already in the tree
	//=======================================================================

	if (r == NULL) {//case 1
		return createNode(v);
	}
		
	if (v > r->value){
		r->right = insert(r->right, v);
	}
	else if (v < r->value) {
		r->left = insert(r->left, v);
	}	
	else{
		return r;
	}//case 2
	//=================================================================
	//update the hight of both old and new roots
	if (getHeight(r->left) > getHeight(r->right)){
		r->height = 1 + getHeight(r->left);
	}
	else {
		r->height = 1 + getHeight(r->right);
	}	
	//===================================================================
	//check if roration reeded
	if (getBalanceFactor(r) > 1 && v < r->left->value) //LL
	{
		return rotateRight(r); //-> pass by pointer reference instead of return and Node* type in the function?? NO as it doesn't return the same node but it returns another root 
	}
	if (getBalanceFactor(r) > 1 && v > r->left->value) //LR
	{
		r->left = rotateLeft(r->left);
		return rotateRight(r);
	}
	if (getBalanceFactor(r) < -1 && v > r->right->value) //RR
	{
		return rotateLeft(r);
	}
	if (getBalanceFactor(r) < -1 && v < r->right->value) //RL
	{
		r->right = rotateRight(r->right);
		return rotateLeft(r);
	}

	return r;//if the node is alreadly balanced
}

void Tree::userInsert(int data) {
	root = insert(root, data);
}

Node* Tree::rotateLeft(Node* oldRoot) {
	Node* newRoot = oldRoot->right;
	Node* leftSide = newRoot->left;

	newRoot->left = oldRoot;
	oldRoot->right = leftSide; //old->right as the value will definatly be grater than the old node

	//update the hight of both old and new roots
	if (getHeight(oldRoot->left) > getHeight(oldRoot->right))
		oldRoot->height = 1 + getHeight(oldRoot->left);
	else 
		oldRoot->height = 1 + getHeight(oldRoot->right);

	if (getHeight(newRoot->left) > getHeight(newRoot->right))
		newRoot->height = 1 + getHeight(newRoot->left);
	else
		newRoot->height = 1 + getHeight(newRoot->right);

	return newRoot;
}

Node* Tree::rotateRight(Node* oldRoot) {
	Node* newRoot = oldRoot->left;
	Node* rightSide = newRoot->right;

	newRoot->right = oldRoot;
	oldRoot->left = rightSide;

	//update the hight of both old and new roots
	if (getHeight(oldRoot->left) > getHeight(oldRoot->right))
		oldRoot->height = 1 + getHeight(oldRoot->left);
	else
		oldRoot->height = 1 + getHeight(oldRoot->right);

	if (getHeight(newRoot->left) > getHeight(newRoot->right))
		newRoot->height = 1 + getHeight(newRoot->left);
	else
		newRoot->height = 1 + getHeight(newRoot->right);

	return newRoot;
}

int Tree::getHeight(Node* n) {
	if (n == NULL)
		return 0;
	return n->height;

}

int Tree::getBalanceFactor(Node* n) {
	if (n == NULL)
		return 0;
	
	return getHeight(n->left) - getHeight(n->right);
}

void Tree::inOrder(Node* n) {
	if (n == NULL)
		return;
	inOrder(n->right);
	order.push_back(n->value);
	inOrder(n->left);
}

vector<int> Tree::getOrder() {
	inOrder(root);
	return order;
}

Tree::~Tree() {

}