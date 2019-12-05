#pragma once
#include "BinaryTree.h"

class BinarySearchTree {
public:
	struct Node {
		Node* left;
		Node* right;
		int data;

		Node() : left(nullptr), right(nullptr) {};
		Node(int d, Node* l = nullptr, Node* r = nullptr) : left(l), data(d), right(r) {};
	};
	Node* root;
public:
	BinarySearchTree();
	~BinarySearchTree();
	Node* Search(int);
	void InsertKey(int);
	bool Exist(int);
private:

};

BinarySearchTree::BinarySearchTree() {

}
BinarySearchTree::~BinarySearchTree() {

}

BinarySearchTree::Node* BinarySearchTree::Search(int key) {
	if (root == nullptr)
		return nullptr;

	Node* aux = root;
	do {
		if (key == aux->data)
			return aux;
		if (key < aux->data && aux->left != nullptr)
			aux = aux->left;
		else if (key > aux->data && aux->right != nullptr)
			aux = aux->right;
	} while (aux->left != nullptr && aux->right != nullptr);

	return nullptr;
}

void BinarySearchTree::InsertKey(int key) {
	if (Search(key) == nullptr) {
		if (root == nullptr)
			root = new Node(key);
		else{
			Node* aux = root;
			while (true) {
				if (key < aux->data) {
					if (aux->left == nullptr) {
						aux->left = new Node(key);
						return;
					}
					else if (key < aux->left->data)
						aux = aux->left;
					else {
						aux->left->right = new Node(key);
						return;
					}
				}
				else {
					if (aux->right == nullptr) {
						aux->right = new Node(key);
						return;
					}
					else if (key > aux->right->data)
						aux = aux->right;
					else {
						aux->right->left = new Node(key);
						return;
					}
				}
			}
		}
	}
}

bool BinarySearchTree::Exist(int key) {
	return false;
}