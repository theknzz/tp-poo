#ifndef __TIPO_NAVIO__
#define __TIPO_NAVIO__

#include "Navio.h"



class Veleiro : public Navio
{
public:
	Veleiro(char t, int n, int p, int qt, int nr, int c, int x, int y)
		:Navio('V', n, 100, 200, qt, nr, x, y) {};
	~Veleiro();
};

class Galeao : public Navio
{
public:
	Galeao(char t, int n, int p, int qt, int nr, int c, int x, int y)
		:Navio('G', n, 100, 400, qt, nr, x, y) {};
	~Galeao();
};

class Escuna : public Navio
{
public:
	Escuna(char t, int n, int p, int qt, int nr, int c, int x, int y)
		:Navio('E', n, 100, qt, nr, x, y) {};
	~Escuna();
};

class Fragata : public Navio
{
public:
	Fragata(char t, int n, int p, int qt, int nr, int c, int x, int y)
		:Navio('F', n, 100, qt, nr, x, y) {};
	~Fragata();
};

class Especial : public Navio
{
public:
	Especial(char t, int n, int p, int qt, int nr, int c, int x, int y)
		:Navio('E', n, 100, qt, nr, x, y) {};
	~Especial();
};

#endif

