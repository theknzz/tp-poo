#ifndef __TIPO_NAVIO__
#define __TIPO_NAVIO__

#include "Navio.h"



class Veleiro : public Navio
{
public:
	Veleiro(char t, int p, int qt, int nr, int c, int x, int y)
		:Navio('V', p, 200, nr, c, x, y) {};
	~Veleiro();
};

class Galeao : public Navio
{
public:
	Galeao(char t, int p, int qt, int nr, int c, int x, int y)
		:Navio('G', p, 400, nr, c, x, y) {};
	~Galeao();
};

class Escuna : public Navio
{
public:
	Escuna(char t, int p, int qt, int nr, int c, int x, int y)
		:Navio('E', p, 100, nr, c, x, y) {};
	~Escuna();
};

class Fragata : public Navio
{
public:
	Fragata(char t, int p, int qt, int nr, int c, int x, int y)
		:Navio('F', p, 500, nr, c, x, y) {};
	~Fragata();
};

class Especial : public Navio
{
public:
	Especial(char t, int p, int qt, int nr, int c, int x, int y)
		:Navio('E', p, qt, nr, c, x, y) {};
	~Especial();
};

#endif

