#pragma once
#include <string>
#include <iostream>
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

	char getTipo();
	Porto* getPorto();
};

ostream& operator<<(ostream& out, Celula c);