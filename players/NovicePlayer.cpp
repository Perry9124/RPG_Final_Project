#include "NovicePlayer.h"
#include "..\players\MagicianPlayer.h"
#include "..\players\OrcPlayer.h"
#include "..\players\KnightPlayer.h"
#include "..\items\AxeWeapon.h"
#include "..\items\SwordWeapon.h"
#include "..\items\TunicArmor.h"
#include "..\items\ShieldArmor.h"
#include "..\items\LifePotion.h"
#include "..\items\MagicPotion.h"
#include <iomanip>
#include <math.h>
#include <windows.h>
#include <algorithm>
#include <conio.h>
#include <fstream>

using namespace std;
NovicePlayer::NovicePlayer() {
	setLevel(1);
	setName("anonymous");
	setJob("NovicePlayer");
	initBackpack();
}
NovicePlayer::NovicePlayer(int l) {
	setLevel(l);
	setName("anonymous");
	setJob("NovicePlayer");
	initBackpack();
}
NovicePlayer::NovicePlayer(int l, string &str) {
	setLevel(l);
	setName(str);
	setJob("NovicePlayer");
	initBackpack();
}
NovicePlayer::NovicePlayer(const NovicePlayer &s) {
	setName(s.getName());
	setLevel(s.getLevel());
	max_hp = s.getMaxHp();
	setHp(s.getHp());
	max_mp = s.getMaxMp();
	setMp(s.getMp());
	attack = s.getAttack();
	defense = s.getDefense();
	setExp(s.getExp());
	lvup_exp = s.getMaxExp();
	setMoney(s.getMoney());
	setJob(s.getJob());
}
NovicePlayer *NovicePlayer::setupPlayer() {
	cout << "Tell me your name, dear adventurer (length int 1 ~ 16) : ";
	string name;
	vector<string> strs;
	ifstream ifs;
	ifs.open("filename.txt");
	if (!ifs.is_open()) {
		cerr << "error happened\n";
	}
	char buffer[256] = { 0 };
	ifs.read(buffer, sizeof(buffer));
	size_t begin, end;
	string delimiter = "\n",str = buffer;
	begin = 0;
	end = str.find(delimiter);
	while (end != string::npos) {
		if (end - begin != 0) {
			strs.push_back(str.substr(begin, end - begin));
		}
		begin = end + delimiter.size();
		end = str.find(delimiter, begin);
	}
	if (begin != str.length()) {
		strs.push_back(str.substr(begin));
	}
	while (true) {
		bool flag = 1;
		cin >> name;
		if (name.size() <= 16) {
			for (size_t i = 0; i < strs.size(); i++) {
				if (name + ".txt" == strs[i])flag = 0;
			}
			if (flag)break;
			else cout << "This name already exist\n";
		}
		else cout << "A shorter please.\n";
	}
	NovicePlayer *p = new NovicePlayer(1, name);
	return p;
}
void NovicePlayer::setLevel(int l) {
	level = l > 0 ? l : 1;	
	int n = (int) log(20) * (getLevel() + 5);
	max_hp = 600 + 10 * n;
	setHp(600 + 10 * n);
	max_mp = 70 + 5 * n;
	setMp(70 + 5 * n);
	attack = 100 + 9 * n;
	defense = 30 + 4 * n;
	setExp(50 * getLevel() *(getLevel() - 1));
	lvup_exp = 50 * getLevel() *(getLevel() + 1);
}
void NovicePlayer::display() {
	cout << "------------------------------------------"
		<< "\nPlayer" << setw(4) << ": " << getName() << setw(17 - getName().size()) << "Hp" << setw(6) << ": " << getHp() << "/" << getMaxHp()
		<< "\nJob" << setw(7) << ": " << getJob() << setw(17 - getJob().size()) << "Mp" << setw(6) << ": " << getMp() << "/" << getMaxMp()
		<< "\nLevel" << setw(5) << ": " << getLevel() << setw(18 - to_string(getLevel()).size()) << "Exp" << setw(5) << ": " << getExp() << "/" << getMaxExp()
		<< "\nAttack" << setw(4) << ": " << getAttack() << setw(20 - to_string(getAttack()).size()) << "Money" << setw(3) << ": " << getMoney()
		<< "\nDefense" << setw(3) << ": " << getDefense()
		<< "\nWeapon "<< setw(3) << ": " << weapon->name << setw(20 - weapon->name.size()) << "Armor" << setw(3) << ": " << armor->name
		<< "\n------------------------------------------\n";
}
string NovicePlayer::serialize() {
	string str;
	str = "nv" + getName() + "," + to_string(getLevel()) + "," + to_string(getHp()) + ","
		+ to_string(getMp()) + "," + to_string(getExp()) + "," + to_string(getMoney());
	string b; // backpack
	for (size_t i = 0; i < backpack.size(); i++) {
		if (backpack[i] == NULL)break;
		size_t s = i;
		while (s < backpack.size() && backpack[s] != NULL && backpack[i]->name == backpack[s]->name) {
			s++;
		}
		b += backpack[i]->name.substr(0, 2) + to_string(s - i);
		if (backpack[s] != NULL) b += ",";
		i = s - 1;
	} // ax,sw,tu,sh,lp,mp
	str += "#" + b;
	return str;
} //  order : name->level->hp->mp->exp->money
NovicePlayer *NovicePlayer::unserialize(string str) {
	if (str.substr(0, 2) == "mg")return MagicianPlayer::unserialize(str);
	if (str.substr(0, 2) == "oc")return OrcPlayer::unserialize(str);
	if (str.substr(0, 2) == "kn")return KnightPlayer::unserialize(str);
	NovicePlayer *p = new NovicePlayer;
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
bool NovicePlayer::levelUp() {
	if (weapon->name != "None") {
		attack -= weapon->attack_increment;
	}
	if (armor->name != "None") {
		defense -= armor->defense_increment;
	}
	int tmp = getExp();
	bool t = false;
	while (lvup_exp <= tmp) {
		setLevel(getLevel() + 1);
		t = true;
	}
	if (weapon->name != "None") {
		attack += weapon->attack_increment;
	}
	if (armor->name != "None") {
		defense += armor->defense_increment;
	}
	return t;
}
void NovicePlayer::initBackpack() {
	backpack.resize(backpack_slot_limit);
	for (int i = 0; i < backpack_slot_limit; i++) {
		backpack[i] = NULL;
	}
}
bool NovicePlayer::putItem(Item *s) {
	if (backpack_weight + s->weight > backpack_weight_limit) {
		return false;
	}
	if (backpack[backpack_slot_limit - 1] != NULL) {
		return false;
	}
	int size = 0;
	for (int i = 0; i < backpack_slot_limit; i++) {
		if (backpack[i] == NULL) {
			backpack[i] = s;
			size = i + 1;
			backpack_weight += s->weight;
			break;
		}
	}
	sort(size);
	return true;
}
void NovicePlayer::sort(int size) {
	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {
			if (*backpack[i] > *backpack[j]) {
				swap(backpack[i], backpack[j]);
			}
		}
	}
} // bubble sort
Item* NovicePlayer::takeItem(int n) {
	if (n < 0 || n >= backpack_slot_limit)return NULL;
	if (backpack[n] != NULL)backpack_weight -= backpack[n]->weight;
	backpack[n] = NULL;
	sort(backpack.size());
	return backpack[n];
}
void NovicePlayer::showBackpack() {
	if (backpack[0] == NULL)cout << "empty\n";
	for (size_t i = 0; i < backpack.size(); i++) {
		if (backpack[i] == NULL)break;
		size_t t = i;
		while (t < backpack.size() && backpack[t] != NULL && backpack[t]->name == backpack[i]->name) {
			t++;
		}
		cout << backpack[i]->name << " * " << t - i << "\n";
		i = t - 1;
	}
}
bool NovicePlayer::equipWeapon(WeaponItem *w, size_t n) {
	if (w->level_required > getLevel())return false;
	if (weapon->name == "None") {
		weapon = w;
		backpack[n] = NULL;
		sort(backpack.size());
		attack += w->attack_increment;
		backpack_weight -= w->weight;
		return true;
	}
	else {
		if (weapon->weight + backpack_weight - w->weight > backpack_weight) {
			return false;
		}
		else {
			attack = attack + w->attack_increment - weapon->attack_increment;
			backpack[n] = NULL;
			putItem(weapon);
			backpack_weight += weapon->weight - w->weight;
			weapon = w;
			return true;
		}
	}
}
bool NovicePlayer::equipArmor(ArmorItem *a, size_t n) {
	if (a->level_required > getLevel())return false;
	if (armor->name == "None") {
		armor = a;
		backpack[n] = NULL;
		sort(backpack.size());
		defense += a->defense_increment;
		backpack_weight -= a->weight;
		return true;
	}
	else {
		if (armor->weight + backpack_weight - a->weight > backpack_weight) {
			return false;
		}
		else {
			defense = defense + a->defense_increment - armor->defense_increment;
			backpack[n] = NULL;
			putItem(armor);
			backpack_weight += armor->weight - a->weight;
			armor = a;
			return true;
		}
	}
}
void NovicePlayer::useConsumable(ConsumableItem *c, size_t n) {
	backpack[n] = NULL;
	for (size_t i = n; i < backpack.size(); i++) {
		if (i + 1 >= backpack.size() || backpack[i + 1] == NULL)break;
		swap(backpack[i], backpack[i + 1]);
	}
	c->use(this);
	backpack_weight -= c->weight;
}
Item* NovicePlayer::item(string str) {
	Item *it = NULL;
	if (str == "Ax") {
		it = dynamic_cast<Item*>(new AxeWeapon);
	}
	else if (str == "Sw") {
		it = dynamic_cast<Item*>(new SwordWeapon);
	}
	else if (str == "Tu") {
		it = dynamic_cast<Item*>(new TunicArmor);
	}
	else if (str == "Sh") {
		it = dynamic_cast<Item*>(new ShieldArmor);
	}
	else if (str == "Li") {
		it = dynamic_cast<Item*>(new LifePotion);
	}
	else if (str == "Ma") {
		it = dynamic_cast<Item*>(new MagicPotion);
	}
	return it;
}