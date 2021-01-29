#pragma once

#include <string>


enum class Actions {
	PhysAttack,
	MagicAttack,
	PhysDefense,
	MagicDefense,
	None,
};

using namespace std;

class Character {

public:

	Character(string name,int vit, int wis, int str, int agi, int def, int arc_def, int ctrl);
	~Character();

	void UpgradeLevel();
	float DoAction(Actions action);

	inline float MagicCrit() { return 1 + (wisdom * (1 + control)); }
	inline float PhysCrit() { return 1 + (wisdom * (1 + strength)); }

public:

	string char_name;
	int vitality;
	int wisdom;
	int strength;
	int agility;
	int defense;
	int arcane_defense;
	int control;
	int level;
	int experience;

	float mod_vitality;
	float mod_wisdom;
	float mod_strength;
	float mod_agility;
	float mod_defense;
	float mod_arcane_defense;
	float mod_control;

	Actions currentAction;
};