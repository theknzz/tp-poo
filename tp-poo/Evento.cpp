#include "Evento.h"

Evento::Evento(int d)
: dur(d){}


int Evento::getDur()
{
	return dur;
}

void Evento::setDur(int n)
{
	dur = n;
}

void Evento::baixaDur()
{
	dur--;
}

Evento::~Evento()
{
}
