#pragma once
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
		myFile.write(reinterpret_cast<char*>(o.data()), sizeof(int)*o.size());
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
		myFile.read(reinterpret_cast<char*>(o.data()), sizeof(int)*len);
	}
	myFile.close();
}

template<class T>
void Save(std::vector<T> o, std::string fileName) {
	std::ofstream myFile;
	myFile.open(fileName, std::ios::binary);
	if (myFile.is_open()) {
		int len = o.size();
		myFile.write(reinterpret_cast<char*>(&len), sizeof(int));
		myFile.write(reinterpret_cast<char*>(o.data()), sizeof(T)*o.size());
	}
	myFile.close();
}

template<class T>
void Recover(std::vector<T> &o, std::string fileName) {
	std::ifstream myFile;
	myFile.open(fileName, std::ios::binary);
	if (myFile.is_open()) {
		int len;
		myFile.read(reinterpret_cast<char*>(&len), sizeof(int));
		o.resize(len);
		myFile.read(reinterpret_cast<char*>(o.data()), sizeof(T)*len);
	}
	myFile.close();
}