#include <sstream>
#include <fstream>
#include <windows.h>
#include <iomanip>
#include <conio.h>
#include "Field.h"
#include "..\misc\Battle.h"
#include "..\monsters\BossMonster.h"
#include "..\monsters\JWMonster.h"
using namespace std;

map<int, string> Field::itos = { {201,"NoviceVillage"}, {202,"GoblinTerritory"},{203, "ZombieTerritory"} 
								,{204,"JWTerritory"},{205,"BossRoom"} };
map<string, int> Field::stop = { {"NoviceVillage.txt",201}, {"GoblinTerritory.txt",202},{"ZombieTerritory.txt",203}
								,{"JWTerritory.txt",204},{"BossRoom.txt",205 } };
map<int, string> Field::pattern = { {0,"  "},{1,"  "},{2,"¢Û"},{3,"¢×"},{4,"¢Ò"},
									{101,"¢Ó"},{102,"¢Ó"},{103,"¢Ó"},
									{200,"¢Ö"},{201,"¢â"},{202,"¢â"},{203,"¢â"},
									{204,"¢â"},{205,"¢â"} };
void SetColor(int color = 7) {
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}
vector<string> Field::split(string s, string delimiter) {
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	string token;
	vector<string> res;
	while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
		token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}
	res.push_back(s.substr(pos_start));
	return res;
}
void Field::Set_board(string filename) {
	ifstream fin;
	fin.open(filename);
	char dir;
	fin >> col >> dir >> row;
	vector<string> strs;
	board = new int*[row];
	for (int i = 0; i < row; i++) {
		board[i] = new int[col];
	}
	for (int i = 0; i < row; i++) {
		string str;
		fin >> str;
		strs = split(str, ",");
		for (int j = 0; j < col; j++) {
			board[i][j] = stoi(strs[j]);
			if (board[i][j] == 0) path.push_back({ i,j });
		}
	}
	fin >> x >> y;
	fin.close();
}
void Field::addRandomIncident(size_t n) {
	if (n > path.size()) {
		cout << "Error happened\n";
		return;
	}
	srand((int)time(NULL));
	while (n > 0) {
		size_t p = rand() % path.size();
		node point = path[p];
		if (board[point.x][point.y] == 0) {
			n--;
			board[point.x][point.y] = 2; // incident
		}
	}
}
Field::Field(vector<NovicePlayer*> players, string Name) {
	// position of player
	teleport = 0;
	Set_board(Name);
	name = Name;
	if (stop[name] > 201) {
		addRandomIncident(5);
	}
}
void Field::move(vector<NovicePlayer*>&players, int d[]) {
	int nx = x + d[0];
	int ny = y + d[1];
	if (board[nx][ny] == 2 && alive) {
		system("cls");
		int u = stop[name] - 201;
		int d = 1;
		vector<BaseMonster*> monsters = BaseMonster::createMonster(2, d, u);
		for (auto m : monsters) {
			m->display();
		}
		Battle battle(players, monsters);
		if (battle.Win()) {
			board[nx][ny] = 0;
			x = nx;
			y = ny;
		}
		else {
			system("cls");
			cout << "After running away\n";
			for (size_t i = 0; i < players.size(); i++) {
				if (players[i]->getHp() == 0)cout << "Player" << i + 1 << " died\n";
				players[i]->display();
			}
			system("pause>nul");
		}
	}
	else if (board[nx][ny] == 4) {
		system("cls");
		vector<BaseMonster*> monsters;
		BossMonster *b = new BossMonster;
		monsters.push_back(b);
		for (int i = 0; i < 3; i++) {
			monsters.push_back(new JWMonster);
		}
		Battle battle(players, monsters);
		if (battle.Win()) {
			end = 1;
			cout << "Congratulation! You win!\n";
			x = nx;
			y = ny;
		}
	}
	else if (board[nx][ny] != 1) {
		x = nx;
		y = ny;
	}
	if (board[nx][ny] > 100 && board[nx][ny] < 200) {
		cout << "\nYou find a friend\n";
		eve->visit(players, board[nx][ny]);
	} // event
}
void Field::display(vector<NovicePlayer*> players, int n) {
	// distance to wall
	int dx = x < row - x ? x : row - x;
	int dy = y < col - y ? y : col - y;
	alive = 0;
	for (size_t i = 0; i < players.size(); i++) {
		if (players[i]->getHp())alive++;
	}
	int sx = x - n / 2 < 0 ? 0 : x - n / 2;
	if (row - x < n / 2 + 1)sx = row - n;
	int sy = y - n / 2 < 0 ? 0 : y - n / 2;
	if (col - y < n / 2 + 1)sy = col - n;
	for (int i = sx; i < sx + n; i++) {
		for (int j = sy; j < sy + n; j++) {
			if (board[i][j] == 1) {
				SetColor(255);
			}  // wall
			else if ((x == i && y == j) || board[i][j] >= 200) {
				SetColor(7);
			}  // begin and end
			else {
				SetColor(47);
			}  // something happened
			if (x == i && y == j) {
				cout << "¡¹";
			}
			else cout << pattern[board[i][j]];
			SetColor(7);
		}
		cout << endl;
	}
	cout << "\nusing them to control\n\n"
		<< "  W\n"
		<< "A S D\n";
	cout << "You are now at (" << x << "," << y << ") of " << name.substr(0,name.find(".")) << "\n";
	if (board[x][y] == 200) {
		cout << "You heal all your Hp and Mp here\n";
		for (size_t i = 0; i < players.size(); i++) {
			players[i]->setHp(players[i]->getMaxHp());
			players[i]->setMp(players[i]->getMaxMp());
		}
		alive = 1;
	}
	else if (board[x][y] > 200)teleport = 1;
	else teleport = 0;
	if (!alive)cout << "\nYour team is all died, you need to go to heal\n";
} // display players' position in a n * n vision
void Field::showBackpack(NovicePlayer *p, size_t n) {
	vector<Item*> b;
	b = p->getBackpack();
	if (b[0] == NULL) {
		system("cls");
		cout << "Player" << n + 1 << ":\n"
			<< "empty\n";
		system("pause>nul");
		return;
	} // no item
	int t = 0;
	while (true) {
		system("cls");
		if (b[0] == NULL) {
			system("cls");
			cout << "Player" << n + 1 << ":\n"
				<< "empty\n";
			system("pause>nul");
			return;
		}
		vector<Item*> v;
		vector<int> num; // number of each item
		int sum = 0;  // sum of weight
		for (size_t i = 0; i < b.size(); i++) {
			if (b[i] == NULL)break;
			size_t s = i;
			while (s < b.size() && b[s] != NULL && b[s]->name == b[i]->name) {
				s++;
			}
			v.push_back(b[i]);
			num.push_back(s - i);
			sum += s - i;
			i = s - 1;
		}
		cout << "Player" << n + 1 << " :\n";
		for (size_t i = 0; i < v.size(); i++) {
			cout << v[i]->name << " * " << num[i];
			if (t == i)cout << setw(15 - v[i]->name.size()) << "<-";
			cout << "\n";
		}
		cout << "Slot : " << sum << "\n"
			<< "Weight : " << p->getWeight() << "/" << p->getWeightLimit() << "\n";
		cout << "W : Up\n"
			<< "S : Down\n"
			<< "B : Back\n"
			<< "Enter : Choose\n";
		int ch = _getch();
		if (ch == 66 || ch == 98) {
			break;
		} // back
		else if (ch == 119 || ch == 87) {
			if (!t) t = v.size() - 1;
			else t--;
		}
		else if (ch == 115 || ch == 83) {
			t = (t + 1) % v.size();
		}
		else if (ch == 13) {
			while (true) {
				system("cls");
				v[t]->show();
				cout << "W : Wear/Use\n"
					<< "B : Back\n"
					<< "T : Throw\n";
				ch = _getch();
				if (ch == 66 || ch == 98) {
					break;
				} // back
				else if (ch == 84 || ch == 116) {
					size_t s;
					for (size_t i = 0; i < b.size(); i++) {
						if (b[i]->name == v[t]->name) {
							s = i;
							p->takeItem(i);
							break;
						}
					}
					system("cls");
					cout << "You throw " << v[t]->name << "\n";
					system("pause>nul");
					break;
				} // throw
				else if (ch == 119 || ch == 87) {
					size_t s;
					for (size_t i = 0; i < b.size(); i++) {
						if (b[i]->name == v[t]->name) {
							s = i;
							break;
						}
					}
					system("cls");
					if (b[s]->type == 'w') {
						WeaponItem *w = dynamic_cast<WeaponItem*>(b[s]);
						if (p->equipWeapon(w, s)) {
							cout << "Player" << n + 1 << " equips " << b[s]->name;
						}
						else cout << "Player" << n + 1 << " failed to equip " << b[s]->name;
					}
					else if (b[s]->type == 'a') {
						ArmorItem *a = dynamic_cast<ArmorItem*>(b[s]);
						if (p->equipArmor(a, s)) {
							cout << "Player" << n + 1 << " equips " << b[s]->name;
						}
						else cout << "Player" << n + 1 << " fail to equip " << b[s]->name;
					}
					else if (b[s]->type == 'c') {
						ConsumableItem *c = dynamic_cast<ConsumableItem*>(b[s]);
						cout << "Player" << n + 1 << " uses " << b[s]->name;
						p->useConsumable(c, s);
					}
					system("pause>nul");
					break;
				} // wear
			}

		}
		b = p->getBackpack();
	}
}
string Field::getMapname() {
	return itos[board[x][y]];
}
string Field::getFilename() {
	return itos[board[x][y]] + ".txt";
}
string Field::serialize() {
	string str;
	str = name + "," + to_string(x) + "," + to_string(y) + "," + eve->serialize();
	return str;
}
Field *Field::unserialize(string str) {
	cout << str << endl;
	Field *f = new Field();
	vector<int> res;
	string delimiter = ",";
	size_t begin, end;
	begin = 0;
	end = str.find(delimiter);
	f->Set_board(str.substr(0, end));
	f->name = str.substr(0, end);
	begin = end + delimiter.size();
	end = str.find(delimiter, begin);
	while (end != string::npos) {
		if (end - begin != 0) {
			res.push_back(stoi(str.substr(begin,end - begin)));
			cout << str.substr(begin, end - begin) << " ";
		}
		begin = end + delimiter.size();
		end = str.find(delimiter, begin);
	}
	if (begin < str.length()) {
		res.push_back(stoi(str.substr(begin)));
		cout << str.substr(begin);
	}
	f->x = res[0];
	f->y = res[1];
	int n = 99;
	for (size_t i = 2; i < res.size(); i++) {
		f->eve->setVisit(n + i, res[i]);
	}
	return f;
}