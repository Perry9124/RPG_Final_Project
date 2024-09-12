#ifndef BATTLE_H
#define BATTLE_H
#include <iostream>
#include "..\monsters\BaseMonster.h"
#include "..\players\NovicePlayer.h"
#include "..\items\Item.h"
using namespace std;
struct Character {
	char type; // p for players, m for monsters
	bool alive = 1; 
	void *instance;  // pointer of the object
};
class Battle {
private:
	Character *ActionList; // order of the monster and players' turn
	const int nPlyr;
	const int nMon;
	static bool win;
	int mon_alive;
	int plyr_alive;
public:
	Battle(vector<NovicePlayer*>, vector<BaseMonster*>); // battle
	int action(vector<NovicePlayer*>, int); // determine player's action
	void dropItem(vector<NovicePlayer*>); // drop item in random
	static bool Win() {
		return win;
	}
};
#endif