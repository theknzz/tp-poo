#ifndef __NAVIOS__
#define __NAVIOS__

#include <string>

using namespace std;

class Navio
{
	char tipo;  // Tipo de embarcação
	int id;   // numero que identificao
	int preco;  // preco
	int qt_agua; // tamanho do reservatorio de agua
	int nr_soldados; // numero de soldados
	int capacidade; // capacidade para mercadoria (toneladas)
	int x, y; // coordenadas

protected:
	static int conta; // criador do id

public:
	Navio(char t, int p, int qt, int nr, int c, int x, int y);

	// funcoes set
	void set_tipo(char t);
	void set_preco(int p);
	void set_agua(int qt);
	void set_soldados(int nr);
	void set_capacidade(int c);
	void set_x(int x);
	void set_y(int y);


	// funcoes get
	char get_tipo()const { return tipo; }
	int get_id()const { return id; }
	int get_preco()const { return preco; }
	int get_agua()const { return qt_agua; }
	int get_soldados()const { return nr_soldados; }
	int get_capacidade()const { return capacidade; }
	int get_x()const { return x; }
	int get_y()const { return y; }
	
	// info
	string getAsString()const;

	// moves
	void movimento(int id);

	~Navio();
};

#endif

