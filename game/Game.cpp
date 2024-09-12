#include "Game.h"
#include <time.h>
#include <algorithm>
#include <windows.h>
#include <fstream>
#include <conio.h>
#include <unordered_set>
using namespace std;

int dir[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };
Game::Game() {
	int t = 0;
	while (true) {
		menu:
		system("cls");
		cout << "Choose one for your game\n";
		cout << "New game";
		if (!t)cout << "<-";
		cout << "\n";
		cout << "Old game";
		if (t)cout << "<-";
		cout << "\nUsing W and S to move and Enter to enter";
		int ch = _getch();
		if (ch == 119 || ch == 87) {
			if (!t)t = 1;
			else t--;
		}
		else if (ch == 115 || ch == 83) {
			t = (t + 1) % 2;
		}
		else if (ch == 13) {
			break;
		}
	}
	system("cls");
	if (t) {
		ifstream ifs;
		ifs.open("filename.txt");
		char buffer[256] = { 0 };
		vector<string> strs;
		ifs.read(buffer, sizeof(buffer));
		string str = buffer,delimiter = "\n";
		size_t begin = 0, end;
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
		int f = 0;
		string filename;
		while (true) {
			system("cls");
			for (size_t i = 0; i < strs.size(); i++) {
				cout << strs[i];
				if (i == f)cout << "<-";
				cout << "\n";
			}
			cout << "Back";
			if (f == strs.size())cout << "<-";
			cout << "\n";
			int ch = _getch();
			if (ch == 87 || ch == 119) {
				if (!f)f = strs.size();
				else f--;
			} // W
			else if (ch == 83 || ch == 115) {
				f = (f + 1) % (strs.size() + 1);
			} // S
			else if (ch == 13) {
				break;
			} // Enter
		}
		if (f == strs.size())goto menu;
		filename = strs[f];
		unserialize(filename);
	}
	else {
		vector<int> v(60);
		for (size_t i = 0; i < v.size(); i++) {
			v[i] = i;
		}
		auto start = v.begin(), end = v.end();
		srand((int)time(0));
		random_shuffle(v.begin(), v.end());
		string str = "story";
		cout << str;
		system("pause>nul");
		system("cls");
		NovicePlayer *p = NovicePlayer::setupPlayer();
		players.push_back(p);
		for (size_t i = 0; i < 2; i++) {
			Item *it = Item::randItem(v[2 * i] % 3 + 1, v[2 * i + 1] % 2 + 1);
			players[0]->putItem(it);
		}
		maze = new Field(players, "NoviceVillage.txt");
	}
}
void Game::run() {
	string filename = players[0]->getName() + ".txt";
	while (true) {
		system("cls");
		maze->display(players, 5);
		cout << "K : Show backpack\n"
			<< "F : Save\n";
		if (maze->Teleport()) {
			cout << "T : go to "<< maze->getMapname() << "\n";
		}
		int ch = _getch();
		if (ch == 115 || ch == 83) {
			maze->move(players, dir[0]);
		} // S
		else if (ch == 119 || ch == 87) {
			maze->move(players, dir[1]);
		} // W
		else if (ch == 100 || ch == 68) {
			maze->move(players, dir[2]);
		} // D
		else if (ch == 97 || ch == 65) {
			maze->move(players, dir[3]);
		} // A
		else if (maze->Teleport() && ch == 116 || ch == 84) {
			maze = new Field(players, maze->getFilename());
		} // Teleport
		else if (ch == 107 || ch == 75) {
			size_t t = 0;
			while (true) {
				system("cls");
				if (players.size() == 1) {
					cout << "Player1\n";
					maze->showBackpack(players[0], 0);
					break;
				}
				else {
					for (size_t i = 0; i < players.size(); i++) {
						cout << "Player" << i + 1;
						if (t == i) cout << "<-";
						cout << endl;
					}
					cout << "B : Back\n"
						<< "Enter : Choose\n"
						<< "W : Up\n"
						<< "S : Down\n";
					int c = _getch();
					if (c == 119 || c == 87) {
						if (!t)t = players.size() - 1;
						else t--;
					} // up
					else if (c == 115 || c == 83) {
						t = (t + 1) % players.size();
					} // down
					else if (c == 13) {
						maze->showBackpack(players[t], t);
					} // choose
					else if (c == 66 || c == 98) {
						break;
					} // back
				}
			}
		} // K show backpack
		else if (ch == 70 || ch == 102) {
			int c;
			while (true) {
				system("cls");
				cout << "Are you sure? (Y/N)\n";
				c = _getch();
				if (c == 89 || c == 121) {
					goto save;
				}
				else if (c == 78 || c == 110)break;
			}
		} // F save
		if (maze->End()) {
			remove(filename.c_str());
			ifstream ifs;
			ifs.open("filename.txt");
			char buffer[256];
			ifs.read(buffer, sizeof(buffer));
			ifs.close();
			vector<string> strs;
			string str = buffer, delimiter = "\n";
			size_t begin = 0, end;
			end = str.find(delimiter);
			while (end != string::npos) {
				if (end - begin != 0) {
					strs.push_back(str.substr(begin, end - begin));
				}
				begin = end + delimiter.size();
				end = str.find(delimiter, begin);
			}
			/*if (begin != str.length()) {
				strs.push_back(str.substr(begin));
			}*/
			ofstream ofs;
			ofs.open("filename.txt");
			for (size_t i = 0; i < strs.size(); i++) {
				if (strs[i] == filename)continue;
				ofs << strs[i] << "\n";
				cout << "i = " << i << strs[i] << "\n";
			}
			break;
		}
	}
	return;
save:
	serialize(filename);
	cout << "\nSave success"
		<< "\nFilename : " << filename;
}
void Game::serialize(string filename) {
	ofstream ofs;
	ofs.open(filename);
	ofs << players.size() << "\n";
	string strp;
	for (size_t i = 0; i < players.size(); i++) {
		strp += players[i]->serialize() + "\n";
	}
	ofs << strp;
	string strm = maze->serialize();
	ofs << strm;
	ofs.close();
	ifstream ifs;
	ifs.open("filename.txt");
	if (!ifs.is_open()) {
		cerr << "filename.txt open failed\n";
	}
	unordered_set<string> strs;
	char buffer[256] = { 0 };
	ifs.read(buffer, sizeof(buffer));
	ifs.close();
	string str = buffer,delimiter = "\n";
	size_t begin = 0, end;
	end = str.find(delimiter);
	while (end != string::npos) {
		if (end - begin != 0) {
			strs.insert(str.substr(begin, end - begin));
		}
		begin = end + delimiter.size();
		end = str.find(delimiter, begin);
	}
	if (begin != str.length()) {
		strs.insert(str.substr(begin));
	}
	if (strs.find(filename) != strs.end())return;
	strs.insert(filename);
	ofstream fout;
	fout.open("filename.txt");
	for (auto v : strs) {
		fout << v << "\n";
	}
	fout.close();
}
void Game::unserialize(string filename) {
	ifstream ifs;
	ifs.open(filename);
	if (!ifs.is_open()) {
		cerr << "error of filename\n";
	}
	string num;
	ifs >> num;
	int n = stoi(num);
	vector<string> strp(n);
	for (int i = 0; i < n; i++) {
		ifs >> strp[i];
		cout << strp[i] << "\n";
		players.push_back(NovicePlayer::unserialize(strp[i]));
	}
	string strm;
	ifs >> strm;
	maze = Field::unserialize(strm);
}