#include "Celula.h"

Celula::~Celula()
{
}

char Celula::getTipo() {
	return tipo;
}

Porto* Celula::getPorto() {
	return porto;
}

ostream& operator<<(ostream& out, Celula c) {
	if (c.getTipo() == 'M')
		out << '.';
	else if (c.getTipo() == 'T')
		out << '+';
	else 
		out << c.getPorto()->getID();
	return out;
}