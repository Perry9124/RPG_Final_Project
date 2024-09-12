#ifndef MAGICPOTION_H
#define MAGICPOTION_H
#include "..\items\ConsumableItem.h"
class MagicPotion : public ConsumableItem{
public:
	MagicPotion(int = 1);
	static Item* randMagic();
};
#endif // !MAGICPOTION_H
