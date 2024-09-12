#include "..\players\MagicianPlayer.h"
#include "..\items\AxeWeapon.h"
#include "..\items\SwordWeapon.h"
#include "..\items\TunicArmor.h"
#include "..\items\ShieldArmor.h"
#include "..\items\LifePotion.h"
#include "..\items\MagicPotion.h"
#include <iostream>

using namespace std;

MagicianPlayer::MagicianPlayer() : NovicePlayer() {
	setLevel(1);
	setJob("MagicianPlayer");
}
MagicianPlayer::MagicianPlayer(int l) : NovicePlayer(l) {
	setLevel(l);
	setJob("MagicianPlayer");
}
MagicianPlayer::MagicianPlayer(int l, string &str) : NovicePlayer(l, str) {
	setLevel(l);
	setJob("MagicianPlayer");
}
MagicianPlayer::MagicianPlayer(const MagicianPlayer &s) : NovicePlayer(s) { }
void MagicianPlayer::setLevel(int l) {
	level = l > 0 ? l : 1;
	//  data for MagicianPlayer
	int n = (int) log(20) * (getLevel() + 5);
	max_hp = 500 + 7 * n;
	setHp(500 + 7 * n);
	max_mp = 100 + 10 * n;
	setMp(100 + 10 * n);
	attack = 120 + 10 * n;
	defense = 30 + 4 * n;
	setExp(50 * getLevel() *(getLevel() - 1));
	lvup_exp = 50 * getLevel() *(getLevel() + 1);
}
void MagicianPlayer::specialSkill() {
	int Hp = getHp() - 10 * getLevel();
	if (Hp <= 0) {
		cout << "No enough hp,failed to pray\n";
		return;
	}
	setHp(Hp);
	int Mp = getMp() + 5 * getLevel();
	setMp(Mp < getMaxMp() ? Mp : getMaxMp());
}
bool MagicianPlayer::levelUp() {
	int tmp = getExp();
	bool t = false;
	while (lvup_exp <= tmp) {
		setLevel(getLevel() + 1);
		t = true;
	}
	return t;
}
string MagicianPlayer::serialize() {
	string str;
	str = "mg" + getName() + "," + to_string(getLevel()) + "," + to_string(getHp()) + ","
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
NovicePlayer *MagicianPlayer::unserialize(string str) {
	NovicePlayer *p = new MagicianPlayer;
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