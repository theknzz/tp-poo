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

bool Jogador::moveNavio(const int id, vector <Celula> mapa) // considerando que o movimento de todos os navios é de uma celula
{
	srand(time(NULL));

	// find Navio de com id = num
	Navio* ob = encontraNav(id);

	if (ob == nullptr)
	{
		return false;
	}
	
	const auto antX = ob->get_x();
	const auto antY = ob->get_y();

	const auto randNr = rand() % 101;
	cout << "random number: " << randNr << endl;

	if (randNr <= 12.5 && randNr >= 0) {
		cout << "direita" << endl;
			// vai para a direita
			ob->set_x(ob->get_x() + 1);
			
			if (ob->get_x() > colunas - 1) { // se a proxima celula ultrapassar os limites à direita
				cout << "eu nao devia estar aqui!" << endl;
				ob->set_x(0);	// ele aparece do lado esquerdo
			}

		cout << "x: " << ob->get_x() << endl;
	}
	else if(randNr <= 25 && randNr > 12.5) {
		cout << "esquerda" << endl;
			// vai para a esquerda
			ob->set_x(ob->get_x() - 1);
		if (ob->get_x() < 0) {
			ob->set_x(colunas - 1);
		}

		cout << "x: " << ob->get_x() << endl;
	}
	else if (randNr <= 37.5 && randNr > 25) {
		cout << "baixo" << endl;
			// vai para baixo
			ob->set_y(ob->get_y() + 1);
		if (ob->get_y() > linhas - 1) {
			ob->set_y(0);
		}

		cout << "y: " << ob->get_y() << endl;
	}
	else if (randNr <= 50 && randNr > 37.5){
		cout << "cima" << endl;
			// vai para cima
			ob->set_y(ob->get_y() - 1);
		if (ob->get_y() < 0) {
			ob->set_y(linhas - 1);
		}

		cout << "y: " << ob->get_y() << endl;
	}
	else if (randNr <= 62.5 && randNr > 50)
	{
		cout << "noroeste" << endl;
		// vai para NO (noroeste)
		ob->set_x(ob->get_x() - 1);
		ob->set_y(ob->get_y() - 1);


		//if(ob->get_y() < 0 && ob->get_x < 0)
		//{
		//	ob->set_y(linhas - 1);
		//	ob->set_x(colunas - 1);
		//}
		cout << "x: " << ob->get_x() << endl;
		cout << "y: " << ob->get_y() << endl;
	}
	else if (randNr <= 75 && randNr > 62.5)
	{
		cout << "nordeste" << endl;
		// vai para NE (nordeste)
		ob->set_x(ob->get_x() + 1);
		ob->set_x(ob->get_x() - 1);
	}
	else if (randNr <= 87.5 && randNr > 75)
	{
		cout << "sudoeste" << endl;
		// vai para SO (sudoeste)
		ob->set_x(ob->get_x() - 1);
		ob->set_y(ob->get_y() + 1);

		cout << "x: " << ob->get_x() << endl;
		cout << "y: " << ob->get_y() << endl;

	}
	else if (randNr <= 100 && randNr > 87.5)
	{
		cout << "sudeste" << endl;
		// vai para SE (sudeste)
		ob->set_x(ob->get_x() + 1);
		ob->set_y(ob->get_y() + 1);

		cout << "x: " << ob->get_x() << endl;
		cout << "y: " << ob->get_y() << endl;
	}

	// se a nova celula for terra -> fica na posicao antiga 'antX/Y'
	if(mapa[colunas*ob->get_y() + ob->get_x()].getTipo() == '+')
	{
		cout << "deixei de ser um barco todo o terreno!" << endl;
		ob->set_x(antX);
		ob->set_y(antY);
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