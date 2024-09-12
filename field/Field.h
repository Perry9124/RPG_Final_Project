#ifndef FIELD_H
#define FIELD_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "..\players\NovicePlayer.h"
#include "..\event\Event.h"
using namespace std;

struct node {
	int x, y;
};
class Field {
private:
	string name; // name of map
	int alive;
	int **board;
	int row; // height of the map
	int col; // length of the map
	vector<node> path;
	Event *eve;
	// players' position
	int x;
	int y;
	bool end = 0; // go to the ending point or not
	static map<int,string> itos;
	static map<string, int> stop;
	bool teleport = 0;
	static map <int,string> pattern;
public:
	Field() {} // default
	Field(vector<NovicePlayer*>, string);
	~Field() {
		for (int i = 0; i < row; i++) {
			delete[] board[i];
		}
		delete[] board;
	}
	void setPos(int r, int c) {
		x = r;
		y = c;
	}
	void move(vector<NovicePlayer*> &players, int d[]);
	vector<string> split(string, string);
	void Set_board(string);
	void addRandomIncident(size_t n = 3);
	void display(vector<NovicePlayer*>,int);
	void showBackpack(NovicePlayer*, size_t);
	bool End() const {
		return end;
	}
	string getMapname();
	string getFilename();
	bool Teleport() const {
		return teleport;
	}
	string serialize();
	static Field* unserialize(string);
};
#endif
