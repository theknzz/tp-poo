#include "Calmaria.h"
#include "Jogo.h"


Calmaria::Calmaria(int coord_x, int coord_y):Evento(4){
	x = coord_x; 
	y = coord_y;
}

void Calmaria::atuaEvento(Jogo* j)
{
	j->evento_calmaria(x, y);
}
Navio* Calmaria::getNavio() { 
	return nullptr;
}
Calmaria::~Calmaria()
{
}
