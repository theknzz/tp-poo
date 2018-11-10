#include "Navio.h"

#include <sstream>
#include <iostream>


Navio::Navio(char t, int n, int p, int qt, int nr, int c, int x, int y)
	: tipo(t), id(n), preco(p), qt_agua(qt), nr_soldados(nr), capacidade(c), x(x), y(y)
{
	cout << getAsString();
}

// -------------------------------------

void Navio::set_tipo(char t)
{
	this->tipo = t;
}

void Navio::set_preco(int p)
{
	if (p < 0) {
		cout << "\nPreco [" << p << "] invalido ..." << endl;
		return;
	}

	this->preco = p;
}

void Navio::set_agua(int qt)
{
	this->qt_agua = qt;
}

void Navio::set_soldados(int nr)
{
	this->nr_soldados = nr;
}

void Navio::set_capacidade(int c)
{
	this->capacidade = c;
}

void Navio::set_x(int x)
{
	this->x = x;
}

void Navio::set_y(int y)
{
	this->y = y;
}

// -------------------------------------

string Navio::getAsString()const
{
	ostringstream oss;

	oss << "\nTipo: " << tipo << "\nId: " << id
		<< "\nPreco: " << preco << "\nQuantidade de agua: " << qt_agua
		<< "\nNumero de soldados: " << nr_soldados << "\nCapacidade: " << capacidade << " (toneladas)"
	<< "\nCoodernadas : " << "{" << x << "," << y << "}" << endl;

	return oss.str();
}

Navio::~Navio()
{
	cout << "\n\n\nGAMEOVER" << endl;
}
