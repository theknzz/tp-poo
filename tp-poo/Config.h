#ifndef __CONFIG__
#define __CONFIG__

#include <vector>
#include "Jogador.h"

#include <fstream>
#include <sstream>

using namespace std;

struct Config {
	int linhas, colunas, moedas, probpirata, preconavio, precoveleiro, precoescuna, precogaleao, precofragata, precoespecial, precosoldado, precovendpeixe, precocompmercad, precovendmercad, soldadosporto, probevento, probtempestade, probsereias, probcalmaria, probmotim;
};
typedef struct Coordenadas {
	int x;
	int y;
	bool operator==(const Coordenadas & a) const {
		return (x == a.x && y == a.y);
	}
}coords;

// le mapa
void var(string s, istringstream &le, Config& cfg);
//vector<Celula> le_fich(Config& cfg, Jogador& jogador);

#endif