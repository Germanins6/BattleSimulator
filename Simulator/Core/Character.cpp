#include "Character.h"

Character::Character(string name, int vit, int wis, int str, int agi, int def, int arc_def, int ctrl) {

	char_name = name;
	vitality = vit;
	wisdom = wis;
	strength = str;
	agility = agi;
	defense = def;
	arcane_defense = arc_def;
	control = ctrl;
	level = 1;
	experience = 150;

	mod_vitality = 1.0f;
	mod_wisdom = 1.0f;
	mod_strength = 1.0f;
	mod_agility = 1.0f;
	mod_defense = 1.0f;
	mod_arcane_defense = 1.0f;
	mod_control = 1.0f;

	currentAction;
}

Character::~Character() {
}

void Character::UpgradeLevel() {

	vitality *= mod_vitality;
	wisdom *= mod_wisdom;
	strength *= mod_strength;
	agility *= mod_agility;
	defense *= mod_defense;
	arcane_defense *= mod_arcane_defense;
	control *= mod_control;
	experience *= 1.5f;
	level++;
}

float Character::DoAction(Actions action) {

	float value;
	
	switch (action)
	{
	case Actions::PhysAttack:
		return value = (strength + 0.1f * vitality) * PhysCrit(); break;
	case Actions::MagicAttack:
		return value = (wisdom + 0.1f * agility + vitality) * MagicCrit(); break;
	case Actions::PhysDefense:
		return value = (defense * strength) * agility; break;
	case Actions::MagicDefense:
		return value = (arcane_defense * control) * agility;  break;
	}

	return 0.0f;
}