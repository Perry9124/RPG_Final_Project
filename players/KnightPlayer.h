#ifndef KNIGHTPLAYER
#define KNIGHTPLAYER

#include "..\players\NovicePlayer.h"
#include <iostream>

using namespace std;

class KnightPlayer : public NovicePlayer {
public:
	KnightPlayer();
	KnightPlayer(int);
	KnightPlayer(int, string&);
	KnightPlayer(const KnightPlayer &s);
	void setLevel(int);
	void specialSkill();
	bool levelUp();
	string serialize();
	static NovicePlayer *unserialize(string);
};
#endif