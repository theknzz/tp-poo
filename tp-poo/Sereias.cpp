#include "Sereias.h"
#include "Jogo.h"

Sereias::Sereias(int n):Evento(1){
	id = n;
}
int Sereias::getID() const {
	return id;
}

void Sereias::setID(int n) {
	id = n;
}
void Sereias::atuaEvento(Jogo *j) {
	j->evento_sereias(id);
}
Navio* Sereias::getNavio() {
	return nullptr;
}
Sereias::~Sereias()
{
}
