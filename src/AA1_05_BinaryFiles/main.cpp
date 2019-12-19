#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "SaveRecover.h"


int main() {
	//Ex 1
	std::vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	SaveVector(vec, "lol.txt");
	std::vector<int> vec2;
	RecoverVector(vec2, "lol.txt");
	for (int i = 0; i < vec2.size(); i++)
		std::cout << vec2[i] << " ";
	std::cout << std::endl;
	//Ex 2
	std::vector<Object> objects = { {'c', 6, 9} , {'z', 48, 10} };
	Save<Object>(objects, "objects.txt");
	std::vector<Object> objects2;
	Recover<Object>(objects2, "objects.txt");
	for (int i = 0; i < objects2.size(); i++)
		std::cout << objects2[i].type << " " << objects2[i].x << " " << objects2[i].y << std::endl;


	return 0;
}