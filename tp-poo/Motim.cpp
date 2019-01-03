#include "Motim.h"
#include "Jogo.h"


Motim::Motim(int n)
:Evento(5){
	id = n;
}

int Motim::getID() const {
	return id;
}

void Motim::setID(int n) {
	id = n;
}

void Motim::atuaEvento(Jogo* j)
{
	bool first = true;
	navio = j->evento_motim(first, getID());
	if(navio==nullptr && first)
	{
		setDur(1);
	}
}

Navio* Motim::getNavio()
{
	return navio;
}

Motim::~Motim()
{
}
