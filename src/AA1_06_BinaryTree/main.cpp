#include "BinaryTree.h"
#include "BinarySearchTree.h"
#include <iostream>

int main() {
	BinaryTree<int> tree;
	std::cout << "Pre-order: ";
	tree.PreOrder();
	std::cout << "\nPre-orderI: ";
	tree.PreOrderI();
	std::cout << "\nPost-order: ";
	tree.PostOrder();
	std::cout << "\nIn-order: ";
	tree.InOrder();
	std::cout << "\nGetNumberNodes: " << tree.GetNumberNodes();
	std::cout << "\nGetNumberNodesI: " << tree.GetNumberNodesI();
	std::cout << "\nHeight: " << tree.Height();
	tree.Empty();
	std::cout << "\nGetNumberNodes after Empty(): " << tree.GetNumberNodes();

	//BinarySearchTree<int> bst;

	return 0;
}