#include "BinaryTree.h"
#include "BinarySearchTree.h"
#include <iostream>

int main() {
	BinaryTree<int> tree;
	std::queue<int> q;
	q.push(-1);
	q.push(-1);
	q.push(-2);
	tree.PrintPath(q);

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





	/*BinarySearchTree bst;
	bst.InsertKey(8);
	bst.InsertKey(3);
	bst.InsertKey(10);
	bst.InsertKey(7);
	bst.InsertKey(1);
	bst.InsertKey(9);*/

	return 0;
}