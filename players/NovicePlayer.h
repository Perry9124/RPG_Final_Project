#ifndef NOVICEPLAYER_H
#define NOVICEPLAYER_H

#include <iostream>
#include <string>
#include <vector>
#include "..\items\Item.h"
#include "..\items\WeaponItem.h"
#include "..\items\ArmorItem.h"
#include "..\items\ConsumableItem.h"
using namespace std;
//  base class
class NovicePlayer {
private:
	string name;
	int hp;
	int mp;
	int exp;
	//int money;
	string job;
	vector<Item*> backpack; // the ¡§inventory¡¨ in many other games
	WeaponItem* weapon = new WeaponItem; // weapon item
	ArmorItem* armor = new ArmorItem; // armor item
	int backpack_weight = 0; // current weight of player¡¦s backpack
protected:
	int level;  // level of player
	int attack;  // attack of player
	int defense;  // defense of player
	int max_hp;  // store max hp of player
	int max_mp;  //  store max mp of player
	int lvup_exp;  //  store needed exp to level up 
	int money;  // money player have
	int backpack_weight_limit = 40; // limit on weight of backpack
	int backpack_slot_limit = 10; // limit on number of backpack¡¦s slots
public:
	NovicePlayer();  //  default constructor
	NovicePlayer(int);  //  only set level for player
	NovicePlayer(int, string&);  //  set up level and name for player
	NovicePlayer(const NovicePlayer &);  //  copy constructor
	void display();  //  for showing the info of player
	void setWeight(int w) {
		backpack_weight = w <= backpack_weight_limit ? w : backpack_weight;
	}
	int getWeight()const {
		return backpack_weight;
	}
	void setWeightLimit(int w) {
		backpack_weight_limit = w > 0 ? w : 0;
	}
	int getWeightLimit() const {
		return backpack_weight_limit;
	}
	void setBackpack_slot_limit(int n) {
		backpack_slot_limit = n;
	}
	int getBackpack_slot_limit()const {
		return backpack_slot_limit;
	}
	void initBackpack(); // set all Item* = NULL
	vector<Item*> getBackpack() const {
		return backpack;
	}
	bool equipWeapon(WeaponItem*, size_t); // equip weapon
	bool equipArmor(ArmorItem*,size_t); // equip armor
	bool putItem(Item*); // add item to backpack
	void sort(int); // sort backpack
	Item* takeItem(int);
	void showBackpack();
	void useConsumable(ConsumableItem *c, size_t i);
	static Item* item(string);
	//  set up and get all information function
	static NovicePlayer* setupPlayer();
	void setName(string str) {
		name = str;
		money = 100;
	}
	string getName() const {
		return name;
	}
	virtual void setLevel(int);  // set up level of player and automatically set other information
	virtual void specialSkill() {}
	virtual string serialize(); // encode a class into a string
	static NovicePlayer* unserialize(string);  // decode a string into class
	int getLevel() const {
		return level;
	}
	void setHp(int Hp) {
		if (Hp < 0)hp = 0;
		else hp = Hp < max_hp ? Hp : max_hp;
	}
	int getHp() const {
		return hp;
	}
	void setMp(int Mp) {
		if (Mp < 0)mp = 0;
		else mp = Mp < max_mp ? Mp : max_mp;
	}
	int getMp() const {
		return mp;
	}
	void setExp(int Exp) {
		exp = Exp;
	}
	int getExp()const {
		return exp;
	}
	void setMoney(int Money) {
		money = Money;
	}
	int getMoney() const {
		return money;
	}
	int getAttack() const {
		return attack;
	}
	int getDefense() const {
		return defense;
	}
	int getMaxHp() const {
		return max_hp;
	}
	int getMaxMp() const {
		return max_mp;
	}
	int getMaxExp() const {
		return lvup_exp;
	}
	void setJob (string str) {
		job = str;
	}
	string getJob() const {
		return job;
	}
	virtual bool levelUp();
};
#endif