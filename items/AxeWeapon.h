#ifndef AXEWEAPON_H
#define AXEWEAPON_H
#include "..\items\WeaponItem.h"
class AxeWeapon : public WeaponItem {
public:
	AxeWeapon() : WeaponItem(3, "Axe", "Add bonus attack", "Just an axe", 5, 30) {}
	static Item* randAxe();
};
#endif