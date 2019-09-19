#include "../../dep/inc/XML/rapidxml.hpp"
#include "../../dep/inc/XML/rapidxml_utils.hpp"
#include "../../dep/inc/XML/rapidxml_iterators.hpp"
#include "../../dep/inc/XML/rapidxml_print.hpp"
#include <map>
#include <sstream>
#include <iostream>
#include "enemy.h"
#include "utils.h"

int main() {
	std::map<std::string, Enemy> enemies;

	rapidxml::xml_document<> doc;
	std::ifstream file("../../res/files/config.xml");
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);

	rapidxml::xml_node<> *pRoot = doc.first_node();
	for (rapidxml::xml_node<> *pNodeI = pRoot->first_node("enemy"); pNodeI; pNodeI = pNodeI->next_sibling()) {
		Enemy aux;
		aux.vitality = std::stoi(pNodeI->first_node("vitality")->value());
		aux.attackDamage =  std::stoi(pNodeI->first_node("damage")->value());
		aux.defense = std::stoi(pNodeI->first_node("defense")->value());
		aux.attackFrequency = std::stoi(pNodeI->first_node("frequency")->value());
		aux.experienceAtDefeat = std::stoi(pNodeI->first_node("experience")->value());
		for (rapidxml::xml_node<> *pNodeII = pNodeI->first_node("weapon"); pNodeII; pNodeII = pNodeII->next_sibling()) {
			Enemy::Weapon aux2;
			aux2.type = pNodeII->first_attribute("type")->value();
			aux2.range = std::stoi(pNodeII->first_attribute("range")->value());
			aux.weapons.insert(std::pair<std::string, Enemy::Weapon>(pNodeII->first_attribute("name")->value(), aux2)); //insert all weapons, Enemy finished
		}
		enemies.insert(std::pair<std::string, Enemy>(pNodeI->first_attribute("name")->value(), aux));	//insert the whole enemy to the map
	}
	doc.clear();

	printEnemies(enemies);

	return 0;
}