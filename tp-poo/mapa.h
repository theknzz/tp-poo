#ifndef __MAPA__
#define __MAPA__

#include <vector>
#include "Celula.h"
#include "Jogador.h"
#include "Config.h"

void mostra_mapa(const Config& cfg, vector<Celula>); // alt = NUMERO DE LINHAS DO MAPA ... larg = NUMERO DE COLUNAS DO MAPA
void mostra_navios(const Config& cfg, const Jogador& jog, vector <Celula> mapa);

#endif