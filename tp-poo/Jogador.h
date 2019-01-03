#ifndef __JOGADOR__
#define __JOGADOR__

#include <vector>
#include <sstream>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <string>

using namespace std;

class Jogador
{
	string nome;
	int moedas;
	int pontuacao;
public:
	Jogador(string na = "player");

	// funcoes get
	int getMoedas()const { return moedas; }
	string getNome()const { return nome; }

	// funcoes set
	void setNome(string na) { nome = na; }
	void setMoedas(int n) { moedas = n; }

	void setPontuacao(int n) { pontuacao = n; }

	string getAsString()const; // falta implementar
		
	~Jogador();
};

#endif