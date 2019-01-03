#ifndef __CALMARIA__
#define __CALMARIA__
#include "Evento.h"

class Calmaria : public Evento
{
	int x, y;
public:
	Calmaria(int coord_x, int coord_y);
	virtual char getTipo() { return 'C'; }
	virtual void atuaEvento(Jogo* j);
	virtual Navio* getNavio();
	virtual int get_x() { return x; }
	virtual int get_y() { return y; }
	virtual ~Calmaria();
};

#endif