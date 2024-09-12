#ifndef ORCPLAYER_H
#define ORCPLAYER_H

#include "..\players\NovicePlayer.h"
#include <iostream>
#include <string>

using namespace std;

class OrcPlayer : public NovicePlayer{
public:
	OrcPlayer();
	OrcPlayer(int);
	OrcPlayer(int, string);
	OrcPlayer(const OrcPlayer &);
	void setLevel(int);
	void specialSkill() { }
	bool levelUp();
	string serialize();
	static NovicePlayer *unserialize(string);
};
#endif