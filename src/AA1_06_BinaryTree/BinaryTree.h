#pragma once
#include <stack>
#include <iostream>
#include <algorithm>
#include <queue>

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

	void PrintPath(std::queue<int>);
private:
	void Empty(Node*);
	void PreOrder(Node*);
	void InOrder(Node*);
	void PostOrder(Node*);
	int GetNumberNodes(Node*);
	int Height(Node*);
	void PrintPath(Node*, std::queue<int>&);
};


template <class T> BinaryTree<T>::BinaryTree() {
	root = nullptr;



	root = new Node(5);
	root->left = new Node(3);
	root->right = new Node(1);
	root->left->left = new Node(2);
	root->right->right = new Node(7);
}
template <class T> BinaryTree<T>::~BinaryTree() {
	Empty();
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

template <class T> void BinaryTree<T>::PrintPath(std::queue<int> v) {
	PrintPath(root, v);
}

template <class T> void BinaryTree<T>::PrintPath(Node* n, std::queue<int> &v) {
	if (n == nullptr)
		return;

	std::cout << n->data << std::endl;
	if (!v.empty()) {
		if (v.front() == -1) {
			v.pop();
			PrintPath(n->left, v);
		}
		else if (v.front() == -2) {
			v.pop();
			PrintPath(n->right, v);
		}
	}
}