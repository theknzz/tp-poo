#include "Jogador.h"
#include "Navio.h"
#include <sstream>
#include <iostream>
#include <ctime>
#include <algorithm>

Jogador::Jogador(int n, string na)
	:moedas(n), nome(na)
{
}

int Jogador::getMoedas()const
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
	return (int)navios.size();
}

Navio* Jogador::encontraNav(const int num) const
{
	for (auto i = 0; i < navios.size(); i++)
		if (navios[i]->get_id() == num)
			return navios[i];

	return nullptr;
}

bool Jogador::moveNavio(const int id, vector <Celula> mapa, const Config& cfg) // considerando que o movimento de todos os navios é de uma celula
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

	// DEBUG: cout << "random number: " << randNr << endl;

	if (randNr <= 12.5 && randNr >= 0) {
		//DEBUG: 		cout << "direita" << endl;
		// vai para a direita
		ob->set_x(ob->get_x() + 1);

		// verificação out of world	
		if (ob->get_x() > cfg.colunas - 1) { // se a proxima celula ultrapassar os limites à direita
			ob->set_x(0);	// ele aparece do lado esquerdo
		}
		cout << "Coords: (" << ob->get_x() << ";" << ob->get_y() << ")" << endl;
	}
	else if (randNr <= 25 && randNr > 12.5) {
		//DEBUG: 		cout << "esquerda" << endl;
		// vai para a esquerda
		ob->set_x(ob->get_x() - 1);

		// verificação out of world		
		if (ob->get_x() < 0) {
			ob->set_x(cfg.colunas - 1);
		}
		cout << "Coords: (" << ob->get_x() << ";" << ob->get_y() << ")" << endl;
	}
	else if (randNr <= 37.5 && randNr > 25) {
		//DEBUG: 		cout << "baixo" << endl;
		// vai para baixo
		ob->set_y(ob->get_y() + 1);

		// verificação out of world	
		if (ob->get_y() > cfg.linhas - 1) {
			ob->set_y(0);
		}
		cout << "Coords: (" << ob->get_x() << ";" << ob->get_y() << ")" << endl;
	}
	else if (randNr <= 50 && randNr > 37.5) {
		//DEBUG: 		cout << "cima" << endl;
		// vai para cima
		ob->set_y(ob->get_y() - 1);

		// verificação out of world	
		if (ob->get_y() < 0) {
			ob->set_y(cfg.linhas - 1);
		}
		cout << "Coords: (" << ob->get_x() << ";" << ob->get_y() << ")" << endl;
	}
	else if (randNr <= 62.5 && randNr > 50)
	{
		//DEBUG: 		cout << "NO" << endl;
		// vai para NO (noroeste)
		ob->set_x(ob->get_x() - 1);
		ob->set_y(ob->get_y() - 1);

		// verificação out of world
		if (ob->get_y() < 0 && ob->get_x() < 0)
		{
			ob->set_y(cfg.linhas - 1);
			ob->set_x(cfg.colunas - 1);
		}
		else if (ob->get_y() > 0 && ob->get_x() < 0)
		{
			ob->set_x(cfg.colunas - 1);
			ob->set_y(ob->get_y());
		}
		else if (ob->get_y() < 0 && ob->get_x() > 0)
			ob->set_y(cfg.linhas - 1);

		cout << "Coords: (" << ob->get_x() << ";" << ob->get_y() << ")" << endl;
	}

	else if (randNr <= 75 && randNr > 62.5)
	{
		//DEBUG:cout << "NE" << endl;
		// vai para NE (nordeste)
		ob->set_x(ob->get_x() + 1);
		ob->set_y(ob->get_y() - 1);

		// verificação out of world
		if (ob->get_y() < 0 && ob->get_x() > cfg.colunas - 1)
		{
			ob->set_y(cfg.linhas - 1);
			ob->set_x(0);
		}
		else if (ob->get_x() > cfg.colunas - 1 && ob->get_y() > 0 && cfg.linhas - 1 > ob->get_y())
		{
			ob->set_x(0);
		}
		else if (ob->get_y() < 0 && ob->get_x() > 0)
			ob->set_y(cfg.linhas - 1);

		cout << "Coords: (" << ob->get_x() << ";" << ob->get_y() << ")" << endl;
	}
	else if (randNr <= 87.5 && randNr > 75)
	{
		//DEBUG: cout << "SO" << endl;
		// vai para SO (sudoeste)
		ob->set_x(ob->get_x() - 1);
		ob->set_y(ob->get_y() + 1);

		// verificação out of world
		if (ob->get_y() > cfg.linhas - 1 && ob->get_x() < 0)
		{
			ob->set_x(cfg.colunas - 1);
			ob->set_y(0);
		}
		else if (ob->get_x() < 0 && ob->get_y() > 0 && cfg.linhas - 1 > ob->get_y())
			ob->set_x(cfg.colunas - 1);
		else if (ob->get_y() > cfg.linhas - 1 && ob->get_x() > 0)
			ob->set_y(0);

		cout << "Coords: (" << ob->get_x() << ";" << ob->get_y() << ")" << endl;

	}
	else if (randNr <= 100 && randNr > 87.5)
	{
		//DEBUG: 
		cout << "SE" << endl;
		// vai para SE (sudeste)
		ob->set_x(ob->get_x() + 1);
		ob->set_y(ob->get_y() + 1);

		// verificação out of world
		if (ob->get_x() > cfg.colunas - 1 && ob->get_y() > cfg.linhas - 1)
		{
			ob->set_x(0);
			ob->set_y(0);
		}
		else if (ob->get_x() > cfg.colunas - 1 && ob->get_y() > 0 && cfg.linhas - 1 > ob->get_y())
			ob->set_x(0);
		else if (ob->get_y() > cfg.linhas - 1 && ob->get_x() > 0)
			ob->set_y(0);

		cout << "Coords: (" << ob->get_x() << ";" << ob->get_y() << ")" << endl;
	}

	// se a nova celula for terra -> fica na posicao antiga 'antX/Y'
	if (mapa[cfg.colunas*ob->get_y() + ob->get_x()].getTipo() == '+')
	{
		//DEBUG: cout << "deixei de ser um barco todo o terreno!" << endl;
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


void Jogador::addPorto(Porto * ob)
{
	portos.push_back(ob);
	sort(portos.begin(), portos.end());
}

//void Jogador::setPrincipal()
//{
//	portoPrincipal = portos[0];
//}

Jogador::~Jogador()
{
}