#pragma once

#include <vector>
#include "Celula.h"

using namespace std;

struct Config {
	int linhas;
	int colunas;
	int moedas;
	int probpirata, preconavio, precosoldado, precovendpeixe, precocompmercad, precovendmercad, soldadosporto, probevento, probtempestade, probsereias, probcalmaria, probmotim;
};

// le mapa
void var(string s, istringstream &le, Config& cfg);
vector<Celula> le_fich(Config& cfg);



