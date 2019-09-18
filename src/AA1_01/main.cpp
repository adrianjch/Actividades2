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
	for (rapidxml::xml_node<> *pNodeI = pRoot->first_node(); pNodeI; pNodeI = pNodeI->next_sibling()) {
		Enemy aux;
		for (rapidxml::xml_node<> *pNodeII = pNodeI->first_node(); pNodeII; pNodeII = pNodeII->next_sibling()) {
			if (pNodeII->name() == static_cast<std::string>("vitality"))
				aux.vitality = std::stoi(pNodeII->value());
			else if (pNodeII->name() == static_cast<std::string>("damage"))
				aux.attackDamage = std::stoi(pNodeII->value());
			else if (pNodeII->name() == static_cast<std::string>("defense"))
				aux.defense = std::stoi(pNodeII->value());
			else if (pNodeII->name() == static_cast<std::string>("frequency"))
				aux.attackFrequency = std::stoi(pNodeII->value());
			else if (pNodeII->name() == static_cast<std::string>("experience"))
				aux.experienceAtDefeat = std::stoi(pNodeII->value());
			else if (pNodeII->name() == static_cast<std::string>("weapon")) {
				//aux.weapons.insert(std::pair<std::string, Enemies::Weapon>(pNodeII->first_attribute()->value(), { pNodeII->first_attribute()->next_attribute()->value(), std::stoi(pNodeII->last_attribute()->value()) }));
				//which one is better?
				Enemy::Weapon aux2;
				aux2.type = pNodeII->first_attribute()->next_attribute()->value();
				aux2.range = std::stoi(pNodeII->last_attribute()->value());
				aux.weapons.insert(std::pair<std::string, Enemy::Weapon>(pNodeII->first_attribute()->value(), aux2));
			}
		}
		enemies.insert(std::pair<std::string, Enemy>(pNodeI->first_attribute()->value(), aux));
	}

	printEnemies(enemies);

	return 0;
}