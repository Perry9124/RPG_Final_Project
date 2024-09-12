#ifndef MAGICIANPLAYER_H
#define MAGICIANPLAYER_H

#include "..\players\NovicePlayer.h"
#include <iostream>
#include <string>

using namespace std;

class MagicianPlayer : public NovicePlayer {
public:
	MagicianPlayer();
	MagicianPlayer(int l);
	MagicianPlayer(int, string&);
	MagicianPlayer(const MagicianPlayer &s);
	void setLevel(int);  //  set up data for magician
	void specialSkill();
	bool levelUp();
	string serialize();
	static NovicePlayer* unserialize(string);
};
#endif