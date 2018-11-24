#ifndef __JOGADOR__
#define __JOGADOR__

#include <vector>
#include "Navio.h"
#include "Celula.h"
#include "Config.h"

using namespace std;

class Navio;
class Porto;

class Jogador
{
	string nome;
	int moedas;
	vector <Navio*> navios;
	vector <Porto*> portos;
	vector <Porto*> portosInimigos;
	//Porto* portoPrincipal;
public:
	Jogador(int n, string na = "player");

	// funcoes get
	int getMoedas()const;
	string getNome()const;

	// funcoes set
	void setNome(string na);
	void pagar(int preco);

	void addNavio(Navio* aux);
	Navio* getNavio(int i) const;
	int GetnNavios() const;
	Navio* encontraNav(int num)const;

	bool moveNavio(int i, vector <Celula> mapa, const Config& cfg);

	string getAsString()const;

	void addPorto(Porto *ob);
	int getPrin_x() const { return portos[0]->get_x(); }
	int getPrin_y() const { return portos[0]->get_y(); }
	// void setPrincipal();
	~Jogador();
};

#endif