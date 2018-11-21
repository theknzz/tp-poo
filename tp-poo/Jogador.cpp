#include "Jogador.h"
#include "Navio.h"
#include <iostream>


Jogador::Jogador(int n,string na)
	:moedas(n), nome(na)
{
}

int Jogador::getmoedas()const
{
	return moedas;
}

vector<Navio> Jogador::addNavio(Navio aux)
{
	navios.push_back(aux);
	return navios;
}


string Jogador::getNome() const
{
	return nome;
}

void Jogador::setNome(string na)
{
	nome = na;
}

void Jogador::pagar(int preco)
{
	moedas -= preco;
}


Jogador::~Jogador()
{
}
