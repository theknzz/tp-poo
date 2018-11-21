#ifndef __CELULA__
#define __CELULA__

#include <string>
#include "Porto.h"

using namespace std;

class Celula
{
	int x, y;
	char tipo; 
	Porto* porto;

public:
	Celula(int a, int b, char t, Porto* p=nullptr)
		:x(a), y(b), tipo(t), porto(p){}

	~Celula();

	char getTipo()const;
	Porto* getPorto()const;

	void setTipo(char c);
};

#endif
