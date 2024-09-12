#ifndef ARMORITEM_H
#define ARMORITEM_H
#include "..\items\Item.h"
class ArmorItem : public Item {
public:
	const int defense_increment;
	ArmorItem() :Item(1, "None", "None", "None", 0, 'a'), defense_increment(0) {}
	ArmorItem(int l, string n, string e, string d, int w, int de) :
		Item(l, n, e, d, w, 'a'), defense_increment(de) {}
	void show() {
		cout << "\nRequired level" << " : " << level_required
			<< "\nName" << setw(13) << " : " << name
			<< "\nDescription" << setw(6) << " : " << description
			<< "\nWeight" << setw(11) << " : " << weight
			<< "\nEffect" << setw(11) << " : "<< "add additonal " << defense_increment << " defense\n";
	}
	static Item* randArmor(int = 0);
};
#endif