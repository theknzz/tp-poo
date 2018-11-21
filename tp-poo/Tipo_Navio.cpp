#include "Tipo_Navio.h"

Veleiro::Veleiro(char t, int p, int qt, int nr, int c, int x, int y)
	:Navio('V', p, 200, nr, c, x, y)
{
	
}
Veleiro::~Veleiro(){}


Galeao::Galeao(char t, int p, int qt, int nr, int c, int x, int y)
	:Navio('G', p, 400, nr, c, x, y)
{
	
}
Galeao::~Galeao(){}

Escuna::Escuna(char t, int p, int qt, int nr, int c, int x, int y)
	:Navio('E', p, 100, nr, c, x, y)
{
	
}
Escuna::~Escuna(){}

Fragata::Fragata(char t, int p, int qt, int nr, int c, int x, int y)
	:Navio('F', p, 500, nr, c, x, y)
{
	
}
Fragata::~Fragata(){}

Especial::Especial(char t, int p, int qt, int nr, int c, int x, int y)
	:Navio('E', p, qt, nr, c, x, y)
{
	
}
Especial::~Especial(){}


