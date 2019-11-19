#include <vector>
#include <string>
#include <fstream>
#include <iostream>

struct object {

};

void SaveVector(std::vector<int> o, std::string fileName) {
	int* vec = new int[o.size()];
	for (int i = 0; i < o.size(); i++)
		vec[i] = o[i];
	delete[] vec;
	std::ofstream myFile;
	myFile.open(fileName, std::ios::binary);
	if (myFile.is_open()) {
		size_t len = sizeof(int)*o.size();
		myFile.write(reinterpret_cast<char*>(&len), sizeof(size_t));
		myFile.write(reinterpret_cast<char*>(&vec), len);
	}
	myFile.close();
}

void RecoverVector(std::vector<int> &o, std::string fileName) {
	std::ifstream myFile;
	myFile.open(fileName, std::ios::binary);
	if (myFile.is_open()) {
		size_t len;
		myFile.read(reinterpret_cast<char*>(&len), sizeof(size_t));
		int* vec = new int[len];
		myFile.read(reinterpret_cast<char*>(&vec), len);
		for (int i = 0; i < len; i++)
			o[i] = vec[i];
		delete[] vec;
	}
	myFile.close();
}

int main() {
	std::vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	SaveVector(vec, "lol.txt");

	std::vector<int> vec2;
	RecoverVector(vec2, "lol.txt");

	for (int i = 0; i < vec2.size(); i++)
		std::cout << vec2[i] << std::endl;

	return 0;
}