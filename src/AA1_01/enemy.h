#pragma once
struct Enemy {
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