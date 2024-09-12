#include "..\items\Item.h"
#include "..\items\WeaponItem.h"
#include "..\items\ArmorItem.h"
#include "..\items\ConsumableItem.h"
Item *Item::randItem(int n, int m) {
	srand((int)time(0));
	if(!n) n = rand() % 3 + 1;
	if(n == 1)return WeaponItem::randWeapon(m);
	else if(n == 2) return ArmorItem::randArmor(m);
	else return ConsumableItem::randConsumable(m);
}
bool operator>(Item &f, Item &s) {
	if (&f == NULL)return true;
	if (&s == NULL)return false;
	if (f.type == 'c') {
		if (s.type != 'c')return true;
		else if (f.name == "MagicPotion") return true;
		return false;
	}
	if (f.type == 'a') {
		if (s.type == 'w')return true;
		else if (s.type == 'a' && f.name == "Shield") return true;
		else return false;
	}
	if (f.type == 'w') {
		if (s.type != 'w')return false;
		else if (f.name == "Sword")return true;
		else return false;
	}
	return false;
} // c > a > w