#ifndef __GALEAO__
#define __GALEAO__

#include "Navio.h"

class Galeao :public Navio
{
	int mercadoria = 0; // quantidade de mercadoria (toneladas)
	int peixe = 0; // quantidade de peixe (toneladas)
public:
	Galeao(int p, int x, int y, int merc, int peixe);
	Galeao(int id, int agua, int sold, int coord_x, int coord_y, bool at, bool mov, int merc, int fish, int preco);

	virtual int getMercadoria() const override { return mercadoria; }
	virtual int getPeixe() const override { return peixe; }
	virtual int maxSoldados(int num) const override;
	virtual void setMercadoria(int quant) override { mercadoria = quant; }
	virtual void setPeixe(int quant) override { peixe = quant; }
	virtual int isFull(int num) const override;
	virtual string getAsString();

	virtual int ando() { return 1; }
	Navio * duplica() const override;

	virtual int cargaLivre();
	virtual void addMercadoria(int quant);
	virtual void addPeixe(int quant);
	virtual int maxAgua();
	virtual int aguaLivre();

	virtual char getTipo() const { return 'G'; }
	virtual void reageTempestade();
	virtual void fazAuto(Jogo * j, int id, vector <string> & ordens);
	virtual void setCliente() {}
	virtual void tiraPeixe(int a);
	virtual void tiraAgua(int quant);
	virtual void resetCliente() {}
	virtual ~Galeao();
};


#endif