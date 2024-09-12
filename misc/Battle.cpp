#include "..\misc\Battle.h"
#include "..\monsters\GoblinMonster.h"
#include "..\monsters\ZombieMonster.h"
#include "..\monsters\JWMonster.h"
#include "..\players\NovicePlayer.h"
#include "..\players\KnightPlayer.h"
#include "..\players\OrcPlayer.h"
#include "..\players\MagicianPlayer.h"
#include <time.h>
#include <windows.h>
#include <conio.h>

bool Battle::win = false;
Battle::Battle(vector<NovicePlayer*> players,vector<BaseMonster*> monsters) : nPlyr(players.size()), nMon(monsters.size()) {
	srand((int)time(0));
	mon_alive = nMon;
	plyr_alive = nPlyr;
	ActionList = new Character[nPlyr + nMon];
	for (int i = 0; i < nPlyr + nMon; i++) {
		if (i < nPlyr) {
			ActionList[i].instance = players[i];
			ActionList[i].type = 'p';
		}
		else {
			ActionList[i].instance = monsters[i - nPlyr];
			ActionList[i].type = 'm';
		}
	}
	int turn = 0;
	while (true) {
		if (ActionList[turn].type == 'p' && ActionList[turn].alive) {
			NovicePlayer *p = static_cast<NovicePlayer*>(ActionList[turn].instance);
			act:
			int t = action(players, turn);
			if (t == 0) {
				int t = 0; //  number of enemy
				while (true) {
					while (!ActionList[t + nPlyr].alive) {
						t = (t + 1) % nMon;
					}
					system("cls");
					for (int i = 0; i < nPlyr; i++) {
						if (!ActionList[i].alive)continue;
						cout << "Player" << i + 1 << "\n";
						players[i]->display();
					} // display players' information
					cout << "\nPlayer" << turn + 1 << " choose one enemy to attack (use Enter to enter)\n";
					for (int i = 0; i < nMon; i++) {
						if (!ActionList[i + nPlyr].alive)continue;
						cout << "Monster" << i + 1 << endl;
						monsters[i]->display();
					} //  display enemies' information
					for (int i = 0; i < nMon; i++) {
						if (!ActionList[i + nPlyr].alive)continue;
						cout << "Monster" << i + 1;
						if (i == t)cout << "  <-";
						cout << endl;
					} // for choose monster
					cout << "back";
					if (t == nMon)cout << "      <-";
					cout << "\n";
					cout << "Using W and S to move and Space to enter\n";
					int ch = _getch();
					if (ch == 87 || ch == 119) {
						if (!t)t = nMon;
						else t--;
						while (!ActionList[t + nPlyr].alive) {
							if (!t)t = nMon;
							else t--;
						}
					}
					else if (ch == 83 || ch == 115) {
						t = (t + 1) % (nMon + 1);
						while (!ActionList[t + nPlyr].alive) {
							t = (t + 1) % (nMon + 1);
						}
					}
					else if (ch == 13) {
						break;
					} // control <-
				}
				if (t == nMon)goto act;
				BaseMonster *def_one = static_cast<BaseMonster*>(ActionList[t + nPlyr].instance);
				cout << "Player" << turn + 1 << " attacks monster" << t + 1 << endl;
				def_one->setHp(def_one->getHp() - (p->getAttack() - def_one->defense > 20 ? p->getAttack() - def_one->defense : 20));
				if (def_one->getHp() == 0) {
					ActionList[t + nPlyr].alive = 0;
					mon_alive--;
					cout << "Monster" << t + 1 << " died\n";
				}
				system("pause>nul");
			}  // normal attack
			else if (t == 1) {
				vector<size_t> n;
				vector<size_t> pos;
				for (size_t i = 0; i < p->getBackpack().size(); i++) {
					if (p->getBackpack()[i] == NULL)break;
					if (p->getBackpack()[i]->type != 'c')continue;
					size_t s = i;
					while (s < p->getBackpack().size() && p->getBackpack()[s] != NULL && 
						p->getBackpack()[s]->name == p->getBackpack()[i]->name) {
						s++;
					}
					pos.push_back(i);
					n.push_back(s - i);
					i = s - 1;
				}
				size_t f = 0;
				while (true) {
					system("cls");
					for (size_t i = 0; i < n.size(); i++) {
						cout << p->getBackpack()[pos[i]]->name << " * " << n[i];
						if (i == f)cout << setw(15 - p->getBackpack()[pos[i]]->name.size()) << "<-";
						cout << "\n";
					}
					cout << "W : Up\n"
						<< "S : Down\n"
						<< "Enter : choose\n"
						<< "B : back\n";
					int ch = _getch();
					if (ch == 13) {
						break;
					} // enter
					else if (ch == 119 || ch == 87) {
						if (!f) f = n.size() - 1;
						else f--;
					} // up
					else if (ch == 115 || ch == 83) {
						f = (f + 1) % n.size();
					} // down
					else if (ch == 66 || ch == 98) {
						goto act;
					}
				}
				system("cls");
				ConsumableItem *c = dynamic_cast<ConsumableItem*>(p->getBackpack()[pos[f]]);
				p->useConsumable(c, pos[f]);
				cout << "After using potion\n";
				p->display();
				system("pause>nul");
			} // using potion
			else if (t == 2) {
				system("cls");
				cout << "Player " << turn + 1 << " uses special skill\n"
					<< "After using special skill\n";
				p->specialSkill();
				p->display();
				system("pause>nul");
			}
		}
		else if (ActionList[turn].type == 'm' && ActionList[turn].alive) { //  automatically attack player
			system("cls");
			BaseMonster *m = static_cast<BaseMonster*>(ActionList[turn].instance);
			cout << "Monster" << turn - nPlyr + 1 << "'s turn\n";
			for (int i = 0; i < nMon; i++) {
				if (!ActionList[i + nPlyr].alive)continue;
				cout << "Monster" << i + 1 << "\n";
				BaseMonster *m = static_cast<BaseMonster*>(ActionList[i + nPlyr].instance);
				m->display();
			}
			NovicePlayer *def_one;
			int t;
			while (true) {
				t = rand() % nPlyr;
				if (ActionList[t].alive) {
					def_one = static_cast<NovicePlayer*>(ActionList[t].instance);
					break;
				}
			}
			cout << "Monster" << turn - nPlyr + 1 << " attack player" << t + 1 << endl;
			def_one->setHp(def_one->getHp() - (m->attack - def_one->getDefense() > 20 ? m->attack - def_one->getDefense() : 20));
			if (def_one->getHp() == 0) {
				ActionList[t].alive = 0;
				plyr_alive--;
				cout << "Player" << t + 1 << " died\n";
			}
			for (int i = 0; i < nPlyr; i++) {
				if (!ActionList[i].alive)continue;
				NovicePlayer *p = static_cast<NovicePlayer*>(ActionList[i].instance);
				cout << "Player" << i + 1 << endl;
				p->display();
			}  // display enemys' information
			system("pause>nul");
		}
		turn = (turn + 1) % (nPlyr + nMon); //  choose the next character
		if (!plyr_alive) {
			system("cls");
			cout << "Battle end, you lose\n";
			win = false;
			system("pause<nul");
			break;
		}
		if (!mon_alive) {
			system("cls");
			win = true;
			int mon = 0, exp = 0;
			for (int i = 0; i < nMon; i++) {
				mon += monsters[i]->money;
				exp += monsters[i]->exp;
			}
			cout << "Battle end, you win\n"
				<< "After battle, your team get " << mon << " money and " << exp << " experience\n";
			for (int i = 0; i < nPlyr; i++) {
				players[i]->setExp(players[i]->getExp() + exp);
				players[i]->setMoney(players[i]->getMoney() + mon);
				if (players[i]->levelUp()) {
					cout << "Player" << i + 1 << " level up!\n";
				}
				players[i]->display();
			}
			dropItem(players);
			system("pause>nul");
			break;
		}
	}
}
int Battle::action(vector<NovicePlayer*>p, int n) {
	if (p[n]->getJob() == "NovicePlayer" || p[n]->getJob() == "OrcPlayer") {
		int t = 0;
		while (true) {
			system("cls");
			for (int i = 0; i < nPlyr; i++) {
				if (!ActionList[i].alive)continue;
				cout << "Player" << i + 1 << "\n";
				p[i]->display();
			}
			for (int i = 0; i < nMon; i++) {
				if (!ActionList[i + nPlyr].alive)continue;
				BaseMonster *m = static_cast<BaseMonster*>(ActionList[i + nPlyr].instance);
				cout << "Monster" << i + 1 << "\n";
				m->display();
			}
			cout << "\n1. Normal attack";
			if (!t)cout << "<-";
			cout << "\n2. Use items";
			if (t == 1)cout << "    <-";
			cout << "\nUsing W and S to move and Enter to enter\n";
			int ch = _getch();
			if (ch == 87 || ch == 119) {
				if (!t) t = 1;
				else t--;
			}
			else if (ch == 83 || ch == 115) {
				t = (t + 1) % 2;
			}
			else if (ch == 13) {
				if (t == 1) {
					bool flag = 0;
					for (size_t i = 0; i < p[n]->getBackpack().size(); i++) {
						if (p[n]->getBackpack()[i] == NULL)break;
						if (p[n]->getBackpack()[i]->type != 'c')continue;
						flag = 1;
					}
					if (flag)break;
					else {
						system("cls");
						cout << "Player" << n + 1 << " don't have any potoin\n";
						system("pause>nul");
					}
				}
				else break;
			}
		}
		return t;
	}
	else {
		int t = 0;
		while (true) {
			system("cls");
			cout << "Player" << n + 1 << "'s turn\n";
			for (int i = 0; i < nPlyr; i++) {
				if (!ActionList[i].alive)continue;
				cout << "Player" << i + 1 << "\n";
				p[i]->display();
			}
			for (int i = 0; i < nMon; i++) {
				if (!ActionList[i + nPlyr].alive)continue;
				BaseMonster *m = static_cast<BaseMonster*>(ActionList[i + nPlyr].instance);
				cout << "Monster" << i + 1 << "\n";
				m->display();
			}
			cout << "\n1. Normal attack";
			if (!t)cout << "<-";
			cout << "\n2. Use items";
			if (t == 1)cout << "    <-";
			cout << "\n3. Special skill";
			if (t == 2)cout << "<-";
			cout << "\nUsing W and S to move and Enter to enter\n";
			int ch = _getch();
			if (ch == 87 || ch == 119) {
				if (!t) t = 2;
				else t--;
			}
			else if (ch == 83 || ch == 115) {
				t = (t + 1) % 3;
			}
			else if (ch == 13) {
				if (t == 1) {
					bool flag = 0;
					for (size_t i = 0; i < p[n]->getBackpack().size(); i++) {
						if (p[n]->getBackpack()[i] == NULL)break;
						if (p[n]->getBackpack()[i]->type != 'c')continue;
						flag = 1;
					}
					if (flag)break;
					else {
						system("cls");
						cout << "Player" << n + 1 << " don't have any potoin\n";
						system("pause>nul");
					}
				}
				else break;
			}
		}
		return t;
	}
}  // 1 for attack, 2 for special skill
void Battle::dropItem(vector<NovicePlayer*> players) {
	srand((int)time(0));
	int t = rand() % 10;
	if (!t) {
		for (size_t i = 0; i < players.size(); i++) {
			cout << "Player" << i + 1;
			Item *it = Item::randItem();
			if (players[i]->putItem(it)) {
				cout << " get " << it->name << "\n";
			}
			else cout << " doesn't get item\n";
		}
	}
}