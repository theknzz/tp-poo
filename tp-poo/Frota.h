#pragma once
#include "Navio.h"

#include <vector>

class Navio;

class Frota
{
	vector <Navio> Nv_jogador;
	vector <Navio> Nv_piratas;
public:
	Frota();


	// funcoes
	void add_navio(char t, int p, int qt, int nr, int c, int x, int y);
	~Frota();
};

