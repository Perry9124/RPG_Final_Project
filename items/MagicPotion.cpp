#include "..\items\MagicPotion.h"
MagicPotion::MagicPotion(int l) :
	ConsumableItem("MagicPotion", "Heal player's mp", "Good to drink", 1, 'l', l) {}
Item* MagicPotion::randMagic() {
	Item* it = new MagicPotion;
	return it;
}