#include <iostream>
#include <string>
#include "..\players\OrcPlayer.h"
#include "..\items\AxeWeapon.h"
#include "..\items\SwordWeapon.h"
#include "..\items\TunicArmor.h"
#include "..\items\ShieldArmor.h"
#include "..\items\LifePotion.h"
#include "..\items\MagicPotion.h"

using namespace std;

OrcPlayer::OrcPlayer() : NovicePlayer() { 
	setLevel(1);
	setJob("OrcPlayer");
}
OrcPlayer::OrcPlayer(int l) : NovicePlayer(l) { 
	setLevel(l);
	setJob("OrcPlayer");
}
OrcPlayer::OrcPlayer(int l, string str) : NovicePlayer(l, str) { 
	setLevel(l);
	setJob("OrcPlayer");
}
OrcPlayer::OrcPlayer(const OrcPlayer &s) : NovicePlayer(s) { }
void OrcPlayer::setLevel(int l) {
	level = l > 0 ? l : 1;
	//  data for OrcPlayer 
	int n = (int) log(20) * (getLevel() + 5);
	max_hp = 800 + 15 * n;
	setHp(800 + 15 * n);
	max_mp = 20 + 5 * n;
	setMp(20 + 5 * n);
	attack = 150 + 12 * n;
	defense = 30 + 2 * n;
	setExp(50 * getLevel() *(getLevel() - 1));
	lvup_exp = 50 * getLevel() *(getLevel() + 1);
}
bool OrcPlayer::levelUp() {
	int tmp = getExp();
	bool t = false;
	while (lvup_exp <= tmp) {
		setLevel(getLevel() + 1);
		t = true;
	}
	return t;
}
string OrcPlayer::serialize() {
	string str;
	str = "oc" + getName() + "," + to_string(getLevel()) + "," + to_string(getHp()) + ","
		+ to_string(getMp()) + "," + to_string(getExp()) + "," + to_string(getMoney());
	string b; // backpack
	for (size_t i = 0; i < getBackpack().size(); i++) {
		if (getBackpack()[i] == NULL)break;
		size_t s = i;
		while (s < getBackpack().size() && getBackpack()[s] != NULL && getBackpack()[i]->name == getBackpack()[s]->name) {
			s++;
		}
		b += getBackpack()[i]->name.substr(0, 2) + to_string(s - i);
		if (getBackpack()[s] != NULL) b += ",";
		i = s - 1;
	} // ax,sw,tu,sh,lp,mp
	str += "#" + b;
	return str;
} //  order : name->level->hp->mp->exp->money
NovicePlayer *OrcPlayer::unserialize(string str) {
	NovicePlayer *p = new OrcPlayer;
	vector<int> res;
	string dir = "#";
	string strp = str.substr(0, str.find(dir));
	string strb = str.substr(strp.size());
	size_t begin, end;
	string delimiter = ",";
	begin = 2;
	end = strp.find(delimiter);
	p->setName(strp.substr(begin, end - begin));
	begin = end + delimiter.size();
	end = strp.find(delimiter, begin);
	while (end != std::string::npos) {
		if (end - begin != 0) {
			res.push_back(stoi(strp.substr(begin, end - begin)));
		}
		begin = end + delimiter.size();
		end = strp.find(delimiter, begin);
	}
	if (begin != strp.length()) {
		res.push_back(stoi(strp.substr(begin)));
	}
	begin = 1;
	end = strb.find(delimiter);
	while (end != std::string::npos) {
		if (end - begin != 0) {
			int num = stoi(strb.substr(begin + 2, end - begin));
			for (int i = 0; i < num; i++) {
				Item *it = item(strb.substr(begin, 2));
				p->putItem(it);
			}
		}
		begin = end + delimiter.size();
		end = strb.find(delimiter, begin);
	}
	if (begin != strb.length()) {
		int num = stoi(strb.substr(begin + 2));
		for (int i = 0; i < num; i++) {
			Item *it = item(strb.substr(begin, 2));
			p->putItem(it);
		}
	}
	p->setLevel(res[0]);
	p->setHp(res[1]);
	p->setMp(res[2]);
	p->setExp(res[3]);
	p->setMoney(res[4]);
	return p;
}