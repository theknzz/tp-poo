#ifndef __NAVIO__
#define __NAVIO__

#include <sstream>
#include <iostream>
#include "Config.h"

using namespace std;

class Jogo;
// struct Config;
class Porto;

class Navio
{
	int id;   // numero que identificao
	int preco;  // preco
	int qt_agua; // quantidade de agua no reservatorio
	int nr_soldados; // numero de soldados
	coords coord; // coordenadas
	bool ativo = true;
	bool moveu = true;
protected:
	static int conta; // criador do id
public:
	Navio(int p, int qt, int nr, int x, int y);
	Navio(int id_novo, int agua, int sold, int x, int y, bool at, bool mov, int preco_c);
	// funcoes set
	void set_preco(int p);
	void set_agua(int qt);
	void set_soldados(int nr);
	virtual void setMercadoria(int quant) = 0;
	virtual void setPeixe(int quant) = 0;
	void set_x(int coord_x);
	void set_y(int coord_y);
	virtual int isFull(int num) const = 0;
	virtual int maxSoldados(int num) const = 0;
	void setMoveu(bool b) { moveu = b; }
	virtual int ando() = 0;

	// funcoes get
	int get_id()const { return id; }
	int get_preco()const { return preco; }
	int get_agua()const { return qt_agua; }
	int get_soldados()const { return nr_soldados; }
	virtual char getTipo() const = 0;
	virtual int getMercadoria() const = 0;
	virtual int getPeixe() const = 0;
	int get_x()const { return coord.x; }
	int get_y()const { return coord.y; }
	bool getMoveu() const { return moveu; }

	// info
	virtual string getAsString() = 0;
	virtual Navio * duplica() const = 0;
	virtual int cargaLivre() = 0;
	virtual void resetCliente() = 0;
	void destruir();
	virtual void addMercadoria(int quant) = 0;
	virtual void addPeixe(int quant) = 0;
	virtual int maxAgua() = 0;
	virtual int aguaLivre() = 0;
	int addAgua(int quant);
	bool isAtivo();
	void setAtivo(bool b) { ativo = b; }
	virtual void tiraAgua(int quant) = 0;
	static Navio* fabrica(char tipo, Config cfg, Porto * p);
	static Navio* fabrica(int x, int y, char tipo, Config cfg);
	virtual void reageTempestade() = 0;
	virtual void fazAuto(Jogo * j, int id, vector <string> & ordens) = 0;
	virtual void tiraPeixe(int a) = 0;
	virtual ~Navio();
};

#endif