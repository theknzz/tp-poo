#ifndef __SEREIAS__
#define __SEREIAS__
#include "Evento.h"


class Sereias : public Evento
{
	int id;
public:
	Sereias(int n);
	int getID() const;
	void setID(int n);
	virtual char getTipo() { return 'S'; }
	virtual void atuaEvento(Jogo* j);
	virtual Navio * getNavio();	
	virtual int get_x() { return -1; }
	virtual int get_y() { return -1; }
	virtual ~Sereias();
};

#endif