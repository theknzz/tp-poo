#ifndef __VELEIRO__
#define __VELEIRO__

#include "Navio.h"

class Veleiro :public Navio{
	int mercadoria = 0; // quantidade de mercadoria (toneladas)
	int peixe = 0; // quantidade de peixe (toneladas)
	int id_cliente;
public:
	Veleiro(int p, int x, int y, int merc, int peixe);
	Veleiro(int id, int agua, int sold, int coord_x, int coord_y, bool at, bool mov, int merc, int fish, int preco);

	virtual int getMercadoria() const override { return mercadoria; }
	virtual int getPeixe() const override { return peixe; }
	virtual int maxSoldados(int num) const override;
	virtual void setMercadoria(int quant) override { mercadoria = quant; }
	virtual void setPeixe(int quant) override { peixe = quant; }
	virtual string getAsString();
	virtual int isFull(int num) const override;
	Navio * duplica() const override;
	virtual int ando() { return rand() % 2 + 1; }
	virtual int cargaLivre();
	virtual void addMercadoria(int quant);
	virtual void addPeixe(int quant);
	virtual int aguaLivre();
	virtual int maxAgua();
	virtual char getTipo() const { return 'V'; }
	virtual void reageTempestade();
	virtual void resetCliente() { id_cliente = -1; }
	virtual void fazAuto(Jogo * j, int id, vector <string> & ordens);
	virtual void tiraPeixe(int a);
	virtual void tiraAgua(int quant);
	virtual ~Veleiro();
};



#endif 