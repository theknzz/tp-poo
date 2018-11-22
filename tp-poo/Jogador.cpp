#include "Jogador.h"
#include "Navio.h"
#include <sstream>
#include <iostream>
#include <ctime>

extern int linhas, colunas, moedas, probpirata, preconavio, precosoldado, precovendpeixe, precocompmercad, precovendmercad, soldadosporto, probevento, probtempestade, probsereias, probcalmaria, probmotim;

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
	srand(time(NULL));

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

	if (randNr_x <= 49) {
		cout << "vou para a direita" << endl;
			// vai para a direita
			ob->set_x(ob->get_x() + 1);
		if (ob->get_x() > colunas - 1) {
			ob->set_x(0);
		}
		cout << "x: " << ob->get_x() << endl;
	}
	else {
		cout << "vou para a esquerda" << endl;
			// vai para a esquerda
			ob->set_x(ob->get_x() - 1);
		if (ob->get_x() < 0) {
			ob->set_x(colunas - 1);
		}
		cout << "x: " << ob->get_x() << endl;
	}
	if (randNr_y >= 49) {
		cout << "vou para a baixo" << endl;
			// vai para baixo
			ob->set_y(ob->get_y() + 1);
		if (ob->get_y() > linhas - 1) {
			ob->set_y(0);
		}
		cout << "y: " << ob->get_y() << endl;
	}
	else{
		cout << "vou para a cima" << endl;
			// vai para cima
			ob->set_y(ob->get_y() - 1);
		if (ob->get_y() < 0) {
			ob->set_y(linhas - 1);
		}
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