#ifndef __COMANDOS__
#define __COMANDOS__
#include "mapa.h"

class Jogador;

class Comandos
{
public:
	// menu
	void menu(Jogador & jogador, vector<Celula> mapa, const Config& cfg) const;

};

#endif