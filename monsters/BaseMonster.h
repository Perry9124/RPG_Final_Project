#ifndef BASEMONSTER_H
#define BASEMONSTER_H
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class BaseMonster{
public:
	BaseMonster();                                     // default constructor
	BaseMonster(string, int, int, int, int, int, int); // constructor
	~BaseMonster() {
		count--;
	}
	void display();
	static int getInstanceCount() {
		return count;
	} //  give number of monsters
	static vector<BaseMonster*> createMonster(int, int, int);
	const string name; //  type of monster
	const int attack;
	const int defense;
	const int exp;     //  experience player can get when it died
	const int money;   //  money player can get when it died
	const int max_hp;  //  max of hp
	const int max_mp;  //  max of mp
	virtual string serialize();
	static BaseMonster *unserialize(string);
	void setHp(int Hp) {
		if (Hp < 0)hp = 0;
		else hp = Hp < max_hp ? Hp : max_hp;
	}
	int getHp() const {
		return hp;
	}
	void setMp(int Mp) {
		if (Mp < 0) mp = 0;
		else mp = Mp < max_mp ? Mp : max_mp;
	}
	int getMp() const {
		return mp;
	}
private:
	int hp;           //  hp of monster, range in [0,max_hp]
	int mp;           //  mp of monster, range in [0,max_mp]
	static int count; //  count how many monsters are there
};
#endif // !BASEMONSTER_H