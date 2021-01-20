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
}

Character::~Character() {
}