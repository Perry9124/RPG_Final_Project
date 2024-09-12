#ifndef SWORDWEAPON_H
#define SWORDWEAPON_H
#include "..\items\WeaponItem.h"
class SwordWeapon : public WeaponItem {
public:
	SwordWeapon() : WeaponItem(5, "Sword", "Add bonus attack", "Just a sword", 10, 60) { }
	static Item* randSword();
};
#endif