#ifndef LIFEPOTION_H
#define LIFEPOTION_H
#include "..\items\ConsumableItem.h"
class LifePotion : public ConsumableItem {
public:
	LifePotion(int = 1); // constructor
	static Item* randLife();
};
#endif //  LIFEPOTION_H