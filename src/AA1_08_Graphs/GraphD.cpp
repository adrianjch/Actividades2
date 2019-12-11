#include "GraphD.h"
#include <algorithm>
#include <iostream>


GraphD::GraphD() {

}
GraphD::GraphD(std::vector<edge> el) {
	for (int i = 0; i < el.size(); i++) {
		Insert(el[i]);
	}
}

void GraphD::Insert(edge e) {
	std::unordered_map<vertex, std::vector<vertex>>::iterator tmp = g.find(e.first);
	if (tmp == g.end()) { // if node doesn't exist in the map
		g.insert({ e.first, std::vector<vertex>(1, e.second) });
	}
	else { // if node already exists in the map
		std::vector<vertex>::iterator it = find(tmp->second.begin(), tmp->second.end(), e.second);
		if (it == tmp->second.end()) // if node doesn't exists in the vector
			tmp->second.push_back(e.second);
	}

	tmp = g.find(e.second);
	if (tmp == g.end()) // if second node doesn't exist in the map
		g.insert({ e.second, std::vector<vertex>() });
}

void GraphD::Remove(edge e) {
	std::unordered_map<vertex, std::vector<vertex>>::iterator tmp = g.find(e.first);
	if (tmp != g.end()) { // if node exists in the map
		std::vector<vertex>::iterator it = find(tmp->second.begin(), tmp->second.end(), e.second);
		if (it != tmp->second.end()) // if node exists in the vector
			tmp->second.erase(it);
	}
}

void GraphD::Print() {
	for (std::unordered_map<vertex, std::vector<vertex>>::iterator it = g.begin(); it != g.end(); it++) {
		std::cout << it->first << "-> ";
		for (std::vector<vertex>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++) {
			std::cout << *it2 << ", ";
		}
		std::cout << std::endl;
	}
}