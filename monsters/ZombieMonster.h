#ifndef ZOMBIEMONSTER_H
#define ZOMBIEMONSTER_H
#include <iostream> 
#include "..\monsters\BaseMonster.h"
class ZombieMonster : public BaseMonster {
public:
	ZombieMonster();
	~ZombieMonster() { }
	string serialize();
	static BaseMonster *unserialize(string);
};
#endif