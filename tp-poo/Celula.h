#pragma once

#include <iostream>
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

ostream& operator<<(ostream& out, Celula c);