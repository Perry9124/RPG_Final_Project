#include "..\items\ConsumableItem.h"
#include "..\items\LifePotion.h"
#include "..\items\MagicPotion.h"
#include "..\players\NovicePlayer.h"
Item* ConsumableItem::randConsumable(int m) {
	srand((int)time(0));
	if(!m) m = rand() % 2 + 1;
	if (m == 1)return LifePotion::randLife();
	else return MagicPotion::randMagic();
}
void ConsumableItem::use(NovicePlayer *p){
	if (type == 'l') {
		p->setHp(p->getHp() + lv * 50);
	}
	else if (type == 'm') {
		p->setMp(p->getMp() + lv * 20);
	}
	else cout << "No type\n";
}