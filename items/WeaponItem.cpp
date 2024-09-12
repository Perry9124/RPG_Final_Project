#include "..\items\WeaponItem.h"
#include "..\items\AxeWeapon.h"
#include "..\items\SwordWeapon.h"
Item* WeaponItem::randWeapon(int m) {
	srand((int)time(0));
	if(!m) m = rand() % 2 + 1;
	if (m == 1) return AxeWeapon::randAxe();
	else return SwordWeapon::randSword();
}