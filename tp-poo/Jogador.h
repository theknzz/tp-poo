#ifndef __JOGADOR__
#define __JOGADOR__

#include <vector>
#include "Navio.h"
#include "Celula.h"

using namespace std;

class Navio;
class Porto;
struct Config;

class Jogador
{
	string nome;
	int moedas;
	vector <Navio*> navios;
	vector <Porto*> portos;
	vector <Porto*> portosInimigos;
	//Porto* portoPrincipal;
public:
	Jogador(string na = "player");

	// funcoes get
	int getMoedas()const;
	string getNome()const;

	// funcoes set
	void setNome(string na);
	void pagar(int preco);
	void setMoedas(int n);

	void addNavio(Navio* aux);
	Navio* getNavio(int i) const;
	int GetnNavios() const;
	Navio* encontraNav(int num)const;

	bool moveNavio(int i, vector <Celula> mapa, const Config& cfg);

	string getAsString()const;

	void addPorto(Porto *ob);

	void mostraPortos() const;

	int getPrin_x() const;
	int getPrin_y() const;
	char getId() const;
	// void setPrincipal();
	~Jogador();
};

#endif