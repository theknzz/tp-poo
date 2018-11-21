#ifndef __JOGADOR__
#define __JOGADOR__

#include <vector>

using namespace std;

class Navio;

class Jogador
{
	string nome;
	int moedas;
	vector <Navio*> navios;
public:
	Jogador(int n,string na = "player");

	// funcoes get
	int getmoedas()const;
	string getNome()const;

	// funcoes set
	void setNome(string na);
	void pagar(int preco);

	void addNavio(Navio* aux);

	string getAsString()const;

	~Jogador();
};

#endif

