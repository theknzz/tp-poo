 
#include "Especial.h"
#include "Jogo.h"

Especial::Especial(int p, int x, int y) : Navio(p, 700, 10, x, y) {
}
Especial::Especial(int id, int agua, int sold, int coord_x, int coord_y, bool at, bool mov, int preco) :
	Navio(id, agua, sold, coord_x, coord_y, at, mov, preco) {}
string Especial::getAsString(){
	ostringstream oss;

	oss << "Tipo: Especial" << "\nId: " << get_id()
		<< "\nPreco: " << get_preco() << "\nQuantidade de agua: " << get_agua()
		<< "\nNumero de soldados: " << get_soldados() << "\nCoodernadas : " << "{" << get_x() << "," << get_y() << "}" << endl;

	return oss.str();
}

Navio * Especial::duplica() const {
	return new Especial(*this);
}

void Especial::addMercadoria(int quant)
{
	return;
}

void Especial::addPeixe(int quant)
{
	return;
}

int Especial::cargaLivre()
{
	return 0;
}

int Especial::maxAgua()
{
	return 700;
}
int Especial::aguaLivre()
{
	return maxAgua() - get_agua();
}

void Especial::reageTempestade()
{
	if (geraNumero(100) < 15)
		destruir();
	set_agua((int)(get_agua() * 0.15));
}

int Especial::maxSoldados(int num) const {
	return 10;
}
int Especial::isFull(int num) const {
	return -1;
}

void Especial::tiraAgua(int quant)
{
	if (quant <= get_agua())
		set_agua(get_agua() - quant);
}

Especial::~Especial()
{
}
