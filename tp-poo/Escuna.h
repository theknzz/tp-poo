#ifndef __ESCUNA__
#define __ESCUNA__

#include "Navio.h"

class Escuna :public Navio
{
	int mercadoria = 0; // quantidade de mercadoria (toneladas)
	int peixe = 0; // quantidade de peixe (toneladas)
public:
	Escuna(int p, int x, int y, int merc, int peixe); 
	Escuna(int id, int agua, int sold, int coord_x, int coord_y, bool at, bool mov, int merc, int fish, int preco);

	virtual int getMercadoria() const override { return mercadoria; }
	virtual int getPeixe() const override { return peixe; }
	virtual int maxSoldados(int num) const override;
	virtual void setMercadoria(int quant) override { mercadoria = quant; }
	virtual void setPeixe(int quant) override { peixe = quant; }
	virtual int isFull(int num) const override;
	virtual string getAsString();

	virtual int cargaLivre();
	virtual void addMercadoria(int quant);
	virtual void addPeixe(int quant);
	virtual int maxAgua();
	virtual int ando() { return 1; }
	virtual char getTipo() const { return 'E'; }
	virtual int aguaLivre();
	Navio * duplica() const override;
	virtual void reageTempestade();
	virtual void fazAuto(Jogo * j, int id, vector <string> & ordens);
	virtual void tiraPeixe(int a); 
	virtual void tiraAgua(int quant);
	virtual void resetCliente() {}

	virtual ~Escuna();
};



#endif