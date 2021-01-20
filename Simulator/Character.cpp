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

	mod_vitality = 0.0f;
	mod_wisdom = 0.0f;
	mod_strength = 0.0f;
	mod_agility = 0.0f;
	mod_defense = 0.0f;
	mod_arcane_defense = 0.0f;
	mod_control = 0.0f;


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