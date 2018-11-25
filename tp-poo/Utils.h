#pragma once
#include <string>
#include <sstream>
#include "Config.h"

class Jogador;
class Celula;
using namespace std;

class Utils
{
public:
	// menu
	static int menu_opt(string s);
	static int opt(int opt, istringstream &iss, Jogador &jogador, const vector <Celula> mapa, const Config& cfg);
};
