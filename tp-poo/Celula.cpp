#include "Celula.h"

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

ostream& operator<<(ostream& out, Celula c) {
	if (c.getTipo() == 'M')
		out << '.';
	else if (c.getTipo() == 'T')
		out << '+';
	else 
		out << c.getPorto()->getID();
	return out;
}
