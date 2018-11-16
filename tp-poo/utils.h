#pragma once
#include <string>
#include <sstream>

class Jogador;
using namespace std;

class Utils
{
public:
	// menu
	static int menu_opt(string s);
	static int opt(int opt, istringstream *iss, Jogador *jogador);

	//vector<vector <char>> le_fich(istream & fich);
};
