#ifndef __TEMPESTADE__
#define __TEMPESTADE__
#include "Evento.h"

class Tempestade :public Evento
{
	int x, y;
public:
	Tempestade(int x, int y);
	virtual char getTipo() { return 'T'; }
	virtual void atuaEvento(Jogo* j);
	virtual Navio* getNavio(){ return nullptr; }
	virtual int get_x() { return x; }
	virtual int get_y() { return y; }
	virtual ~Tempestade();
};

#endif