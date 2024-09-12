#ifndef GAME_H
#define GAME_H
#include "..\players\NovicePlayer.h"
#include "..\field\Field.h"
class Game {
private:
	Field* maze;
	vector<NovicePlayer*> players;
	string mapname;
public:
	Game();
	void run();
	void serialize(string);
	void unserialize(string);
};
#endif