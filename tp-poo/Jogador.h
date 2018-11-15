#pragma once
#include <vector>

using namespace std;

class Navio;

class Jogador
{
	int moedas;
	vector <Navio> Nv_jogador;
	vector <Navio> Nv_piratas;
public:
	Jogador(int n);

	~Jogador();
};

