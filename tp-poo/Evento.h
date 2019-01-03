#ifndef __EVENTO__
#define __EVENTO__
class Jogo;
struct Config;
class Navio;
class Evento
{
	int dur;
public:
	Evento(int d);
	virtual char getTipo() = 0;
	virtual void atuaEvento(Jogo* j) = 0;
	int getDur();
	void setDur(int n);
	void baixaDur();
	virtual	Navio* getNavio() = 0;	
	virtual int get_x() = 0;
	virtual int get_y() = 0;
	virtual ~Evento();

};

#endif
