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