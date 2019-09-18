#include "../../dep/inc/XML/rapidxml.hpp"
#include "../../dep/inc/XML/rapidxml_utils.hpp"
#include "../../dep/inc/XML/rapidxml_iterators.hpp"
#include "../../dep/inc/XML/rapidxml_print.hpp"
#include <map>
#include <sstream>


struct Enemies {
	struct Weapon {
		std::string type;
		int range;
	};
	int vitality;
	int attackDamage;
	int defense;
	int attackFrequency;
	int experienceAtDefeat;
	std::map<std::string, Weapon> weapons;
};


int main() {
	std::map<std::string, Enemies> enemies;

	rapidxml::xml_document<> doc;
	std::ifstream file("../../res/files/config.xml");
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);

	rapidxml::xml_node<> *pRoot = doc.first_node();
	for (rapidxml::xml_node<> *pNodeI = pRoot->first_node(); pNodeI; pNodeI = pNodeI->next_sibling()) {
		Enemies aux;
		for (rapidxml::xml_node<> *pNodeII = pNodeI->first_node(); pNodeII; pNodeII = pNodeII->next_sibling()) {
			if (pNodeII->name() == "vitality")
				aux.vitality = std::stoi(pNodeII->value());
			else if (pNodeII->name() == "damage")
				aux.attackDamage = std::stoi(pNodeII->value());
			else if (pNodeII->name() == "defense")
				aux.defense = std::stoi(pNodeII->value());
			else if (pNodeII->name() == "frequency")
				aux.attackFrequency = std::stoi(pNodeII->value());
			else if (pNodeII->name() == "experience")
				aux.experienceAtDefeat = std::stoi(pNodeII->value());
			else if (pNodeII->name() == "weapon") {
				//aux.weapons.insert(std::pair<std::string, Enemies::Weapon>(pNodeII->first_attribute()->value(), { pNodeII->first_attribute()->next_attribute()->value(), std::stoi(pNodeII->last_attribute()->value()) }));
				//which one is better?
				Enemies::Weapon aux2;
				aux2.type = pNodeII->first_attribute()->next_attribute()->value();
				aux2.range = std::stoi(pNodeII->last_attribute()->value());
				aux.weapons.insert(std::pair<std::string, Enemies::Weapon>(pNodeII->first_attribute()->value(), aux2));
			}
		}
		enemies.insert(std::pair<std::string, Enemies>(pNodeI->name(), aux));
	}
	return 0;
}