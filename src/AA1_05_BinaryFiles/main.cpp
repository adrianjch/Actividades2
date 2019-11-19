#include <vector>
#include <string>
#include <fstream>
#include <iostream>

struct Object {
	char type;
	int x;
	int y;
};

void SaveVector(std::vector<int> o, std::string fileName) {
	std::ofstream myFile;
	myFile.open(fileName, std::ios::binary);
	if (myFile.is_open()) {
		int len = o.size();
		myFile.write(reinterpret_cast<char*>(&len), sizeof(int));
		for (int i = 0; i < o.size(); i++)
			myFile.write(reinterpret_cast<char*>(&o[i]), sizeof(int));
	}
	myFile.close();
}

void RecoverVector(std::vector<int> &o, std::string fileName) {
	std::ifstream myFile;
	myFile.open(fileName, std::ios::binary);
	if (myFile.is_open()) {
		int len;
		myFile.read(reinterpret_cast<char*>(&len), sizeof(int));
		o.resize(len);
		for (int i = 0; i < len; i++) {
			int aux;
			myFile.read(reinterpret_cast<char*>(&aux), sizeof(int));
			o[i] = aux;
		}
	}
	myFile.close();
}

void Save(std::vector<Object> o, std::string fileName) {
	std::ofstream myFile;
	myFile.open(fileName, std::ios::binary);
	if (myFile.is_open()) {
		int len = o.size();
		myFile.write(reinterpret_cast<char*>(&len), sizeof(int));
		for (int i = 0; i < o.size(); i++)
			myFile.write(reinterpret_cast<char*>(&o[i]), sizeof(Object));
	}
	myFile.close();
}

void Recover(std::vector<Object> &o, std::string fileName) {
	std::ifstream myFile;
	myFile.open(fileName, std::ios::binary);
	if (myFile.is_open()) {
		int len;
		myFile.read(reinterpret_cast<char*>(&len), sizeof(int));
		o.resize(len);
		for (int i = 0; i < len; i++) {
			Object aux;
			myFile.read(reinterpret_cast<char*>(&aux), sizeof(Object));
			o[i] = aux;
		}
	}
	myFile.close();
}

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
	Save(objects, "objects.txt");
	std::vector<Object> objects2;
	Recover(objects2, "objects.txt");
	for (int i = 0; i < objects2.size(); i++)
		std::cout << objects2[i].type << " " << objects2[i].x << " " << objects2[i].y << std::endl;


	return 0;
}