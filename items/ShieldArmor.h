#ifndef SHIELDARMOR_H
#define SHIELDARMOR_H
#include "..\items\ArmorItem.h"
class ShieldArmor : public ArmorItem {
public:
	ShieldArmor() :ArmorItem(5, "Shield", "Add bouns defense", "Just a shield", 5, 60) {}
	static Item* randShield();
};
#endif