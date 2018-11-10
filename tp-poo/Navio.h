#ifndef __NAVIOS__
#define __NAVIOS__

#include <string>

using namespace std;

class Navio
{
	char tipo;  // Tipo de embarcação
	const int id;   // numero que identificao
	const int preco;  // preco
	int qt_agua; // tamanho do reservatorio de agua
	int nr_soldados; // numero de soldados
	int capacidade; // capacidade para mercadoria (toneladas)

public:
	Navio(char t,int n, int p, int qt, int nr, int c);


	// funcoes set
	void set_tipo(char t);
	void set_id(int n);
	void set_preco(int p);
	void set_agua(int qt);
	void set_soldados(int nr);
	void set_capacidade(int c);


	// funcoes get
	char get_tipo()const { return tipo; }
	int get_id()const { return id; }
	int get_preco()const { return preco; }
	int get_agua()const { return qt_agua; }
	int get_soldados()const { return nr_soldados; }
	int get_capacidade()const { return capacidade; }

	// info

	string getAsString()const;

	~Navio();
};

#endif

