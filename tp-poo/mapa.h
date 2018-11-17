#pragma once
#include <vector>
#include "Celula.h"
#include "Consola.h"

void mostra_mapa(int alt,int larg,vector<Celula>); // alt = NUMERO DE LINHAS DO MAPA ... larg = NUMERO DE COLUNAS DO MAPA
vector<Celula> le_mapa(vector<Celula> cel);