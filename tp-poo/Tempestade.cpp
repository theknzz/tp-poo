#include "Tempestade.h"
#include "Jogo.h"


Tempestade::Tempestade(int a, int b)
:Evento(1) {
	x = a;
	y = b;
}

void Tempestade::atuaEvento(Jogo* j)
{
	j->evento_tempestade(x, y);
}


Tempestade::~Tempestade()
{
}
