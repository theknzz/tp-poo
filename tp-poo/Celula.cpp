#include "Celula.h"
#include <iostream>


Celula::~Celula()
{
}

char Celula::getTipo()const {
	return tipo;
}

Porto* Celula::getPorto()const {
	return porto;
}

void Celula::setTipo(char c)
{
	tipo = c;
}
