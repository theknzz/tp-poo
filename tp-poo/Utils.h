#pragma once
#include <string>
#include <sstream>
#include "Config.h"

class Jogador;
class Celula;
using namespace std;

class Utils
{
	//const int moedas, probpirata, preconavio, precosoldado, precovendpeixe, precompmercad, precovendemercad, soldadosporto;
	//// eventos
	//const int probevento, probtempestade, probsereias, probcalmaria, probmotim;
public:
	// Utils(string nome);

	// menu
	static int menu_opt(string s);
	static int opt(int opt, istringstream &iss, Jogador &jogador,const vector <Celula> mapa, const Config& cfg);

};



