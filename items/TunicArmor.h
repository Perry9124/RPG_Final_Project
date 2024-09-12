#ifndef TUNICARMOR_H
#define TUNICARMOR_H
#include "..\items\ArmorItem.h"
class TunicArmor : public ArmorItem {
public:
	TunicArmor() :ArmorItem(3, "Tunic", "Add bouns defense", "Just a tunic", 3, 40) {}
	static Item* randTunic();
};
#endif