#include "..\monsters\JWMonster.h"
using namespace std;
JWMonster::JWMonster() : BaseMonster("JW",200, 150, 300, 90, 1000, 400) { }
string JWMonster::serialize() {
	string str;
	str = name + "," + to_string(getHp()) + "," + to_string(getMp());
	return str;
}
BaseMonster *JWMonster::unserialize(string str) {
	BaseMonster *j= new JWMonster;
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
	j->setHp(res[1]);
	j->setMp(res[2]);
	return j;
}