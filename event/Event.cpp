#include "Event.h"
#include "..\players\MagicianPlayer.h"
#include "..\players\KnightPlayer.h"
#include "..\players\OrcPlayer.h"
map<int, bool> Event::vis = { {101,0},{102,0},{103,0} };
Event::Event() {}
void Event::visit(vector<NovicePlayer*> &players, int n) {
	if (!vis[n]) {
		vis[n] = 1;
		NovicePlayer *p = new NovicePlayer;
		if (n == 101)p = new MagicianPlayer;
		if (n == 102)p = new KnightPlayer;
		if (n == 103)p = new OrcPlayer;
		players.push_back(p);
	}
}
string Event::serialize() {
	string str;
	for (int i = 101; i < 104; i++) {
		str += to_string(vis[i]);
		if (i < 103)str += ",";
	}
	return str;
}
Event *Event::unserialize(string str) {
	Event *e = new Event;
	string dir = ",";
	size_t begin = 0, end = str.find(dir);
	int n = 101;
	while (end != string::npos) {
		if (end - begin != 0) {
			if(stoi(str.substr(begin, end - begin)))e->vis[n] = 1;
			n++;
		}
		begin = end + dir.size();
		end = str.find(dir, begin);
	}
	if (begin != str.length()) {
		if (stoi(str.substr(begin)))e->vis[n] = 1;
	}
	return e;
}