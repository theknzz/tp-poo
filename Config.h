#ifndef __CONFIG__
#define __CONFIG__

#include <vector>
#include "Celula.h"
#include "Jogador.h"

using namespace std;

struct Config {
	int linhas, colunas, moedas, probpirata, preconavio, precosoldado, precovendpeixe, precocompmercad, precovendmercad, soldadosporto, probevento, probtempestade, probsereias, probcalmaria, probmotim;
};

// le mapa
void var(string s, istringstream &le, Config& cfg);
vector<Celula> le_fich(Config& cfg, Jogador& jogador);

#endif