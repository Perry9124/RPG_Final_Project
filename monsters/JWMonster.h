#ifndef JWMONSTER_H
#define JWMONSTER_H
#include <iostream>
#include "..\monsters\BaseMonster.h"
class JWMonster : public BaseMonster {
public:
	JWMonster();
	~JWMonster() { }
	string serialize();
	static BaseMonster *unserialize(string);
};
#endif