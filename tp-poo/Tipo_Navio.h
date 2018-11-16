#ifndef __TIPO_NAVIO__
#define __TIPO_NAVIO__

#include "Navio.h"

class Veleiro : public Navio
{
public:
	Veleiro(char t, int p, int qt, int nr, int c, int x, int y);

	~Veleiro();
};

class Galeao : public Navio
{
public:
	Galeao(char t, int p, int qt, int nr, int c, int x, int y);
	~Galeao();
};

class Escuna : public Navio
{
public:
	Escuna(char t, int p, int qt, int nr, int c, int x, int y);
	~Escuna();
};

class Fragata : public Navio
{
public:
	Fragata(char t, int p, int qt, int nr, int c, int x, int y);
	~Fragata();
};

class Especial : public Navio
{
public:
	Especial(char t, int p, int qt, int nr, int c, int x, int y);
	~Especial();
};

#endif

