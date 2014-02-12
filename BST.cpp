//============================================================================
// Name        : FirstCpp.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cmath>

using namespace std;

class Node {
	public:
		Node(int key, Node *left, Node *right): key(key), left(left), right(right){}
		int key;
		Node *left;
		Node *right;
};

void insert(Node * & root, int key){
	if(root == 0)
		root = new Node(key, 0, 0);
	else if(key > root->key)
		insert(root->right, key);	//if key is bigger than current key, insert right
	else if(key < root->key)
		insert(root->left, key);	//if key is smaller than current key, insert left
}

void inTraverse(Node * root){
	if(root != 0){
		inTraverse(root->left);
		cout << "Value: " << root->key << endl;
		inTraverse(root->right);
	}
}

void preTraverse(Node * root){
	if(root != 0){
		cout << "Value: " << root->key << endl;
		inTraverse(root->left);
		inTraverse(root->right);
	}
}

void postTraverse(Node * root){
	if(root != 0){
		inTraverse(root->left);
		inTraverse(root->right);
		cout << "Value: " << root->key << endl;
	}
}

Node search(Node * root, int key){
	if(root != 0){
		if(key == root->key) return *root;
		search(root->left, key);
		search(root->right, key);
	} else {
		return 0;
	}
}


int main() {
	Node *root = 0;
	for(int i=0; i != 20; ++i) insert(root, rand() % 100);
	inTraverse(root);
	return 0;
}
