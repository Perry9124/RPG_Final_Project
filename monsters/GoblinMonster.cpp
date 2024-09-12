#include "..\monsters\GoblinMonster.h"

GoblinMonster::GoblinMonster() :BaseMonster("Goblin", 80, 60, 100, 50, 300, 200) { }
string GoblinMonster::serialize() {
	string str;
	str = name + "," + to_string(getHp()) + "," + to_string(getMp());
	return str;
}
BaseMonster *GoblinMonster::unserialize(string str) {
	BaseMonster *g = new GoblinMonster;
	vector<int> res;
	string delimiter = ",";
	size_t begin = 0, end = str.find(delimiter);
	end = str.find(delimiter, begin);
	begin = end + delimiter.size();
	while (end != std::string::npos) {
		if (end - begin != 0) {
			res.push_back(stoi(str.substr(begin, end - begin)));
		}
		begin = end + delimiter.size();
		end = str.find(delimiter, begin);
	}
	if (begin != str.length()) {
		res.push_back(stoi(str.substr(begin)));
	}
	g->setHp(res[1]);
	g->setMp(res[2]);
	return g;
}