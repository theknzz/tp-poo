#pragma once
#include <vector>

using namespace std;

class Navio;

class Jogador
{
	int moedas;
	//vector <Navio> navios;
public:
	Jogador(int n);

	int getmoedas()const;
	bool addNavio(const Navio * const  navio);

	// funcoes set
	void pagar(int preco);
	~Jogador();
};

