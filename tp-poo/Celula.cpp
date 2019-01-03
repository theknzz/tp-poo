#include "Celula.h"

Celula::~Celula()
{
}
char Celula::getTipo()const {
	return tipo;
}
bool Celula::isPorto()const {
	if (porto == nullptr)
		return false;
	return true;
}
Porto * Celula::getPorto() const {
	return porto;
}

void Celula::setTipo(char c)
{
	tipo = c;
}

int Celula::getPeixe() const {
	return peixe;
}

void Celula::setPeixe(int n) {
	peixe = n;
}

void Celula::addPeixe() {
	peixe += 1;
}

int Celula::get_x() const { 
	return x;
}
int Celula::get_y() const {
	return y;
}
void Celula::set_x(int n) {
	x = n;
}
void Celula::set_y(int n) {
	y = n;
}
bool Celula::pesca() {
	if (peixe == 1){
		peixe = -2;
		return true;
	}
	return false;
}

void Celula::setPorto(Porto * p)
{
	porto = p;
}