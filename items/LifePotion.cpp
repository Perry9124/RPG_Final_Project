#include "..\items\LifePotion.h"
LifePotion::LifePotion(int l) :
	ConsumableItem("LifePotion", "Heal player's hp", "Good to drink", 1, 'l', l) {}
Item* LifePotion::randLife() {
	Item* it = new LifePotion;
	return it;
}