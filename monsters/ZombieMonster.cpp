#include "..\monsters\ZombieMonster.h"
using namespace std;
ZombieMonster::ZombieMonster() : BaseMonster("Zombie", 150, 150, 200, 70, 600, 300){ }
string ZombieMonster::serialize() {
	string str;
	str = name + "," + to_string(getHp()) + "," + to_string(getMp());
	return str;
}
BaseMonster *ZombieMonster::unserialize(string str) {
	BaseMonster *z = new ZombieMonster;
	vector<int> res;
	size_t begin, end;
	string delimiter = ",";
	end = str.find(delimiter);
	begin = 0;
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
	z->setHp(res[1]);
	z->setMp(res[2]);
	return z;
}