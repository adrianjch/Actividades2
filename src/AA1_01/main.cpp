#include "../../dep/inc/XML/rapidxml.hpp"
#include "../../dep/inc/XML/rapidxml_utils.hpp"
#include "../../dep/inc/XML/rapidxml_iterators.hpp"
#include "../../dep/inc/XML/rapidxml_print.hpp"
#include <string>


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
};


int main() {
	rapidxml::xml_document<> doc;

	return 0;
}