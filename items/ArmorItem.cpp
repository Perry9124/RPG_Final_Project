#include "..\items\ArmorItem.h"
#include "..\items\TunicArmor.h"
#include "..\items\ShieldArmor.h"
Item* ArmorItem::randArmor(int m) {
	srand((int)time(0));
	if(!m) m = rand() % 2 + 1;
	if (m == 1) return TunicArmor::randTunic();
	else return ShieldArmor::randShield();
}