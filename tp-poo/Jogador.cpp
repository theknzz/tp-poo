#include "Jogador.h"



Jogador::Jogador(int n)
	:moedas(n)
{
}

int Jogador::getmoedas()const
{
	return moedas;
}

void Jogador::pagar(int preco)
{
	moedas -= preco;
}


Jogador::~Jogador()
{
}
