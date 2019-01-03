#ifndef __ESPECIAL__
#define __ESPECIAL__

#include "Navio.h"

class Especial :public Navio
{
public:
	Especial(int p, int x, int y);
	Especial(int id, int agua, int sold, int coord_x, int coord_y, bool at, bool mov, int preco);

	virtual string getAsString();

	virtual int getMercadoria() const { return -1; }
	virtual int getPeixe() const { return -1; }
	virtual void setMercadoria(int quant) {}
	virtual void setPeixe(int quant) {}
	virtual int isFull(int num) const;
	virtual int maxSoldados(int num) const;

	Navio * duplica() const override;
	virtual void addMercadoria(int quant);
	virtual void addPeixe(int quant);
	virtual int cargaLivre(); 
	virtual int maxAgua();
	virtual int aguaLivre();
	virtual int ando() { return 1; }
	virtual char getTipo() const { return 'S'; }
	virtual void reageTempestade();
	virtual void fazAuto(Jogo * j, int id, vector <string> & ordens) {}
	virtual void resetCliente() {}
	virtual void tiraPeixe(int a) {}
	virtual void tiraAgua(int quant);

	~Especial();
};

#endif