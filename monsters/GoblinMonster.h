#ifndef GOBLINMONSTER_H
#define GOBLINMONSTER_H
#include <iostream>
#include "..\monsters\BaseMonster.h"
class GoblinMonster : public BaseMonster {
public:
	GoblinMonster();
	~GoblinMonster() { }
	string serialize();
	static BaseMonster *unserialize(string);
};
#endif