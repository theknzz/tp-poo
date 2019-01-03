#ifndef __MOTIM__
#define __MOTIM__

#include "Evento.h"
class Navio;
class Motim : public Evento
{
	int id;
	Navio * navio = nullptr;
public:
	Motim(int id);
	int getID() const;
	void setID(int n);
	virtual char getTipo() { return 'M'; }
	virtual void atuaEvento(Jogo* j);
	virtual Navio* getNavio();	
	virtual int get_x() { return -1; }
	virtual int get_y() { return -1; }
	virtual ~Motim();
};

#endif // !__MOTIM__
