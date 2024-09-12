#ifndef ITEM_H
#define ITEM_H
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <time.h>
using namespace std;

class Item {
	friend bool operator>(Item&, Item&);
public:
	const int level_required;
	const string name;
	const string effect;
	const string description;
	const int weight;
	const char type; // determine the type of item
	Item() : level_required(1), name("None"), effect("None"), description("None"), weight(0), type('n') {}
	Item(int l, string n, string e, string d, int w, char t) :
		// level_required->name->effect->description->weight->type
		level_required(l), name(n), effect(e), description(d), weight(w), type(t) {}
	static Item* randItem(int = 0, int = 0);
	virtual void show() = 0;
};
#endif