#ifndef EVENT_H
#define EVENT_H
#include <iostream>
#include <map>
#include <string>
#include "..\players\NovicePlayer.h"
using namespace std;
class Event {
public:
	Event();
	void visit(vector<NovicePlayer*>&,int = 0);
	string serialize();
	static Event* unserialize(string);
	void setVisit(int n, bool t) {
		vis[n] = t;
	}
	bool getVisit(int n) {
		return vis[n];
	}
private:
	static map<int, bool> vis;
};
#endif
