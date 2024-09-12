#include "BaseMonster.h"
#include "..\monsters\GoblinMonster.h"
#include "..\monsters\JWMonster.h"
#include "..\monsters\ZombieMonster.h"
#include <iomanip>
int BaseMonster::count = 0;
BaseMonster::BaseMonster() 
	:name("none"),attack(0),defense(0),exp(0),money(0),max_hp(1),max_mp(0){
	count++;
	setHp(1);
	setMp(0);
}
BaseMonster::BaseMonster(string str, int att, int def, int Exp, int Money, int hp, int mp)
	:name(str), attack(att), defense(def), exp(Exp), money(Money), max_hp(hp), max_mp(mp) {
	count++;
	setHp(hp);
	setMp(mp);
}
vector<BaseMonster*> BaseMonster::createMonster(int n, int down, int up) {
	vector<BaseMonster*> monsters(n);
	for (int i = 0; i < n; i++) {
		int m = rand() % (up - down + 1) + down;
		switch (m) {
		case 1:
			monsters[i] = new GoblinMonster;
			break;
		case 2:
			monsters[i] = new ZombieMonster;
			break;
		case 3:
			monsters[i] = new JWMonster;
			break;
		default:
			break;
		}
	}
	return monsters;
}
void BaseMonster::display() {
	cout << "------------------------------------------"
		<< "\nName" << setw(6) << ": " << name
		<< "\nAttack" << setw(4) << ": " << attack
		<< "\nDefense" << setw(3) << ": " << defense
		<< "\nHp" << setw(8) << ": " << getHp() << "/" << max_hp
		<< "\nMp" << setw(8) << ": " << getMp() << "/" << max_mp
		<< "\n------------------------------------------\n";
}
string BaseMonster::serialize() {
	string str;
	str = name + "," + to_string(hp) + "," + to_string(mp);
	return str;
}
BaseMonster *BaseMonster::unserialize(string str) {
	if (str.substr(0, str.find(',')) == "Goblin")return GoblinMonster::unserialize(str);
	if (str.substr(0, str.find(',')) == "ZombieMonster")return ZombieMonster::unserialize(str);
	if (str.substr(0, str.find(',')) == "JWMonster")return JWMonster::unserialize(str);
	else {
		BaseMonster *b = new BaseMonster;
		return b;
	}
}