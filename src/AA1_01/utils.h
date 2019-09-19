#pragma once
void printEnemies(const std::map<std::string, Enemy> &enemies) {
	std::cout << "Name\tVit\tDmg\tDef\tFreq\tExp\tWeapons" << std::endl << std::endl;
	for (std::map<std::string, Enemy>::const_iterator it = enemies.cbegin(); it != enemies.cend(); it++) {
		std::cout << it->first << '\t' << it->second.vitality << '\t' << it->second.attackDamage << '\t' << it->second.defense << '\t' << it->second.attackFrequency << '\t' << it->second.experienceAtDefeat << '\t';
		for (std::map<std::string, Enemy::Weapon>::const_iterator it2 = it->second.weapons.cbegin(); it2 != it->second.weapons.cend(); it2++) {
			std::cout << it2->first << " (" << it2->second.type << ", " << it2->second.range << ") | ";
		}
		std::cout << std::endl;
	}
}