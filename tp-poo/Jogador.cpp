#include "Jogador.h"
#include "Navio.h"
#include <sstream>
#include <iostream>


Jogador::Jogador(int n, string na)
	:moedas(n), nome(na)
{
}

int Jogador::getmoedas()const
{
	return moedas;
}

void Jogador::addNavio(Navio *aux)
{
	navios.push_back(aux);
}

Navio* Jogador::getNavio(int i) const {
	return navios[i];
}

int Jogador::GetnNavios() const {
	return navios.size();
}

Navio* Jogador::encontraNav(const int num) const
{
	for (auto i = 0; i < navios.size(); i++)
		if (navios[i]->get_id() == num)
			return navios[i];

	return nullptr;
}

bool Jogador::moveNavio(int i)
{
	// find Navio de com id = num
	Navio* ob = encontraNav(i);
	if (ob == nullptr)
	{
		return false;
	}

	// rands sao sempre iguais 
	// x = 41
	// y = 67
	const auto randNr_x = rand() % 100;
	const auto randNr_y = rand() % 100;

	cout << "X: " << randNr_x << endl;
	cout << "Y: " << randNr_y << endl;

	if (randNr_x <= 49) {
		ob->set_x(ob->get_x() + 1);
		cout << "x: " << ob->get_x() << endl;
	}
	else {
		ob->set_x(ob->get_x() - 1);
		cout << "x: " << ob->get_x() << endl;
	}
	if (randNr_y >= 49) {
		ob->set_y(ob->get_y() + 1);
		cout << "y: " << ob->get_y() << endl;
	}
	else{
		ob->set_y(ob->get_y() - 1);
		cout << "y: " << ob->get_y() << endl;
	}

	return true;
}

string Jogador::getAsString() const
{
	ostringstream oss;

	for (Navio *p : navios)
		oss << endl << p->getAsString();

	return oss.str();
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