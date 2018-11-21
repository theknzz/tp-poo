#ifndef __MAPA__
#define __MAPA__

#include <vector>
#include "Celula.h"
#include "Jogador.h"

void mostra_mapa(int alt,int larg,vector<Celula>); // alt = NUMERO DE LINHAS DO MAPA ... larg = NUMERO DE COLUNAS DO MAPA
void mostra_navios(int alt, int larg, const Jogador& jog);
vector<Celula> le_mapa();

#endif
