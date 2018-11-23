#ifndef __JOGADOR__
#define __JOGADOR__

#include <vector>
#include "Navio.h"
#include "Celula.h"

using namespace std;

class Navio;

class Jogador
{
	string nome;
	int moedas;
	vector <Navio*> navios;
public:
	Jogador(int n, string na = "player");

	// funcoes get
	int getmoedas()const;
	string getNome()const;

	// funcoes set
	void setNome(string na);
	void pagar(int preco);

	void addNavio(Navio* aux);
	Navio* getNavio(int i) const;
	int GetnNavios() const;
	Navio* encontraNav(int num)const;

	bool moveNavio(int i, vector <Celula> mapa);

	string getAsString()const;

	~Jogador();
};

#endif
