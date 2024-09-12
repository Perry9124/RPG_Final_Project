#ifndef WEAPONITEM_H
#define WEAPONITEM_H
#include "..\items\Item.h"
using namespace std;
class WeaponItem : public Item {
public:
	const int attack_increment;
	WeaponItem() : Item(1, "None", "None", "None", 0, 'w'), attack_increment(0) {}
	WeaponItem(int l, string n, string e, string d, int w, int a) :
		// level_required->name->description->effect->weight->attack_increment
		Item(l, n, e, d, w, 'w'), attack_increment(a) {}
	void show() {
		cout << "\nRequired level" << " : " << level_required
			<< "\nName" << setw(13) << " : " << name
			<< "\nDescription" << setw(6) << " : " << description
			<< "\nWeight" << setw(11) << " : " << weight
			<< "\nEffect" << setw(11) << " : " << "add additonal " << attack_increment << " attack\n";
	}
	static Item* randWeapon(int = 0);
};
#endif