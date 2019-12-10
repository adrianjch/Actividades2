#pragma once
#include <unordered_map>

typedef int vertex;
typedef std::pair<int, int> edge;

class GraphD {
private:
	std::unordered_map<vertex, std::vector<vertex>> g;
public:
	GraphD();
	GraphD(std::vector<edge>);
	void Insert(edge);
	void Remove(edge);
	void Print();
};