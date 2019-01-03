#ifndef __FRAGATA__
#define __FRAGATA__

#include "Navio.h"

class Fragata :public Navio
{
	int id_protege = -1;
public:
	Fragata(int p, int x, int y);
	Fragata(int id, int agua, int sold, int coord_x, int coord_y, bool at, bool mov, int preco);
	virtual string getAsString();
	virtual int getMercadoria() const { return -1; }
	virtual int getPeixe() const { return -1; }
	virtual int isFull(int num) const override;
	virtual int maxSoldados(int num) const override;
	virtual void setMercadoria(int quant) {}
	virtual void setPeixe(int quant) {}
	virtual int ando() { return rand() % 2 + 1; }
	Navio * duplica() const override;

	virtual int cargaLivre();
	virtual int aguaLivre();
	virtual void addMercadoria(int quant);
	virtual void addPeixe(int quant);
	virtual int maxAgua();
	virtual char getTipo() const { return 'F'; }
	virtual void reageTempestade();
	virtual void fazAuto(Jogo * j, int id, vector <string> & ordens);
	virtual void tiraPeixe(int a) {}
	virtual void tiraAgua(int quant);
	virtual void resetCliente() {}
	~Fragata();
};

#endif