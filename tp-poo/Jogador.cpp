#include "Jogador.h"



Jogador::Jogador(int n)
	:moedas(n)
{
}

int Jogador::getmoedas()const
{
	return moedas;
}

bool Jogador::addNavio(const Navio* const navio)
{
	if (navio == nullptr)
		return false;

	//navios.push_back(Navio(navio));
	
}

void Jogador::pagar(int preco)
{
	moedas -= preco;
}


Jogador::~Jogador()
{
}
