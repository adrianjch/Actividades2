#pragma once
#include <stack>
#include <iostream>
#include <algorithm>

template <class T>
class BinaryTree {
protected:
	struct Node {
		Node* left;
		Node* right;
		T data;

		Node() : left(nullptr), right(nullptr) {};
		Node(T d, Node* l = nullptr, Node* r = nullptr) : left(l), data(d), right(r) {};
	};
	Node* root;
public:
	BinaryTree();
	~BinaryTree();
	void PreOrder();
	void PreOrderI();
	void InOrder();
	void PostOrder();
	int GetNumberNodes();
	int GetNumberNodesI();
	int Height();
	void Empty();
private:
	void Empty(Node*);
	void PreOrder(Node*);
	void InOrder(Node*);
	void PostOrder(Node*);
	int GetNumberNodes(Node*);
	int Height(Node*);
};


template <class T> BinaryTree<T>::BinaryTree() {
	root = new Node(6);
	root->left = new Node(30);
	root->left->left = new Node(15);
	root->left->right = new Node(2);
	root->left->right->left = new Node(0);
	root->right = new Node(60);
}
template <class T> BinaryTree<T>::~BinaryTree() {
	Empty();
}
template <class T> void BinaryTree<T>::Empty() {
	Empty(root);
	root = nullptr;
}
template <class T> void BinaryTree<T>::Empty(Node* n) {
	if (n == nullptr)
		return;

	Empty(n->left);
	n->left = nullptr;
	Empty(n->right);
	n->right = nullptr;
	
	delete n;
}

template <class T> void BinaryTree<T>::PreOrder() {
	PreOrder(root);
}
template <class T> void BinaryTree<T>::PreOrder(Node* n) {
	if (n == nullptr)
		return;

	std::cout << n->data << " ";
	PreOrder(n->left);
	PreOrder(n->right);
}
template <class T> void BinaryTree<T>::PreOrderI() {
	if (root == nullptr)
		return;

	std::stack<Node*> aux;
	aux.push(root);
	Node* tmp;
	while (!aux.empty()) {
		tmp = aux.top();
		aux.pop();
		std::cout << tmp->data << " ";
		if (tmp->right != nullptr)
			aux.push(tmp->right);
		if (tmp->left != nullptr)
			aux.push(tmp->left);
	}
}

template <class T> void BinaryTree<T>::InOrder() {
	InOrder(root);
}
template <class T> void BinaryTree<T>::InOrder(Node* n) {
	if (n == nullptr)
		return;
	InOrder(n->left);
	std::cout << n->data << " ";
	InOrder(n->right);
}

template <class T> void BinaryTree<T>::PostOrder() {
	PostOrder(root);
}
template <class T> void BinaryTree<T>::PostOrder(Node* n) {
	if (n == nullptr)
		return;

	PostOrder(n->left);
	PostOrder(n->right);
	std::cout << n->data << " ";
}

template <class T> int BinaryTree<T>::GetNumberNodes() {
	return GetNumberNodes(root);
}
template <class T> int BinaryTree<T>::GetNumberNodes(Node* n) {
	if (n == nullptr)
		return 0;

	return 1 + GetNumberNodes(n->left) + GetNumberNodes(n->right);
}
template <class T> int BinaryTree<T>::GetNumberNodesI() {
	if (root == nullptr)
		return 0;
	Node* tmp;
	int counter = 0;
	std::stack<Node*> aux;
	aux.push(root);
	while (!aux.empty()) {
		counter++;
	    tmp = aux.top(); 
		aux.pop();
		if (tmp->left != nullptr)
			aux.push(tmp->left);
		if (tmp->right != nullptr)
			aux.push(tmp->right);
	}

	return counter;
}

template <class T> int BinaryTree<T>::Height() {
	return Height(root);
}
template <class T> int BinaryTree<T>::Height(Node* n) {
	if (n == nullptr)
		return 0;

	return 1 + std::max(Height(n->left), Height(n->right));
}