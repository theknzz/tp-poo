 
#include "Escuna.h"
#include "Jogo.h"

Escuna::Escuna(int p, int x, int y, int merc = 0, int fish = 0):Navio(p, 100, 10, x, y)
{
	mercadoria = merc;
	peixe = fish;
}
Escuna::Escuna(int id, int agua, int sold, int coord_x, int coord_y, bool at, bool mov, int merc, int fish, int preco)
	: Navio(id, agua, sold, coord_x, coord_y, at, mov, preco), mercadoria(merc), peixe(fish) {}

string Escuna::getAsString(){
	ostringstream oss;

	oss << "Tipo: Escuna" << "\nId: " << get_id()
		<< "\nPreco: " << get_preco() << "\nQuantidade de agua: " << get_agua()
		<< "\nNumero de soldados: " << get_soldados() << "\nCapacidade: " << getMercadoria() << " (toneladas)"
		<< "\nCoodernadas : " << "{" << get_x() << "," << get_y() << "}" << endl;

	return oss.str();
}

int Escuna::cargaLivre(){
	return 20 - (peixe + mercadoria);
}

void Escuna::addMercadoria(int quant)
{
	if (quant > cargaLivre())
		mercadoria += cargaLivre();
	else
		mercadoria += quant;
}

void Escuna::addPeixe(int quant)
{
	if (quant > cargaLivre())
		peixe += cargaLivre();
	else
		peixe += quant;
}

int Escuna::maxAgua()
{
	return 100;
}
int Escuna::aguaLivre()
{
	return maxAgua() - get_agua();
}
int Escuna::isFull(int num) const {
	if (peixe + mercadoria == 20)
		return 0;
	else if (peixe + mercadoria + num >= 20)
		return 20 - (peixe + mercadoria);
	else
		return num;
}
Navio* Escuna::duplica() const {
	return new Escuna(*this);
}
int Escuna::maxSoldados(int num) const {
	if (get_soldados() == 10)
		return 0;
	else if (num + get_soldados() > 10)
		return 10 - (get_soldados());
	else
		return num;
}

void Escuna::reageTempestade()
{
	set_agua(maxAgua());
	if (geraNumero(100) < 35)
	{
		destruir();
	}
	else if (geraNumero(100) < 20)
	{
		mercadoria = 0;
		peixe = 0;
	}
}

void Escuna::fazAuto(Jogo * j, int id, vector <string> & ordens) {
	int pos = j->pesquisaNavio(id);
	if (cargaLivre() == 0) {
		j->escunaAutoFull(pos, ordens);
	}
	j->escunaAuto(pos, ordens);
}

void Escuna::tiraPeixe(int a) {
	peixe -= a;
}

void Escuna::tiraAgua(int quant)
{
	if (quant <= get_agua())
		set_agua(get_agua() - quant);
}

Escuna::~Escuna()
{
}
