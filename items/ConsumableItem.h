#ifndef CONSUMABLEITEM_H
#define CONSUMABLEITEM_H
#include <iostream>
#include "..\items\Item.h"
using namespace std;
class NovicePlayer;
class ConsumableItem : public Item {
public:
	const char type; // type of potion
	const int lv; // to determine the effect of item
	ConsumableItem():
		Item(1, "None", "None", "None", 0, 'c'), type('n'), lv(1) {}
	ConsumableItem(string s1, string s2, string s3, int w, char t,int l) : 
		type(t), lv(l), Item(1, s1, s2, s3, w, 'c') {}
	void use(NovicePlayer *p);
	void show() {
		cout << "\nRequired level" << " : " << level_required
			<< "\nName" << setw(13) << " : " << name
			<< "\nDescription" << setw(6) << " : " << description
			<< "\nWeight" << setw(11) << " : " << weight
			<< "\nEffect" << setw(11) << " : " << effect << "\n";
	}
	static Item* randConsumable(int = 0);
};
#endif
