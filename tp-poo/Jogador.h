#pragma once
#include <vector>

using namespace std;

class Navio;

class Jogador
{
	int moedas;
	vector <Navio*> Navios;
public:
	Jogador(int n);

	int getmoedas()const;

	// funcoes set
	void pagar(int preco);
	~Jogador();
};

