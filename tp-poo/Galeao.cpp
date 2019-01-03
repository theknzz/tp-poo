 
#include "Galeao.h"
#include "Jogo.h"

Galeao::Galeao(int p, int x, int y, int merc = 0, int fish = 0) : Navio(p, 400, 40, x, y) {
	mercadoria = merc;
	peixe = fish;
}
Galeao::Galeao(int id, int agua, int sold, int coord_x, int coord_y, bool at, bool mov, int merc, int fish, int preco)
	: Navio(id, agua, sold, coord_x, coord_y, at, mov, preco), mercadoria(merc), peixe(fish) {}

string Galeao::getAsString(){
	ostringstream oss;

	oss << "Tipo: Galeao" << "\nId: " << get_id()
		<< "\nPreco: " << get_preco() << "\nQuantidade de agua: " << get_agua()
		<< "\nNumero de soldados: " << get_soldados() << "\nCapacidade: " << getMercadoria() << " (toneladas)"
		<< "\nCoodernadas : " << "{" << get_x() << "," << get_y() << "}" << endl;

	return oss.str();
}
int Galeao::isFull(int num) const {
	if (get_soldados() == 70)
		return 0;
	else if (peixe + mercadoria == 70)
		return 0;
	else if (peixe + mercadoria + num >= 70)
		return 70 - (peixe + mercadoria);
	else
		return num;
}
int Galeao::maxSoldados(int num) const {
	if (get_soldados() == 40)
		return 0;
	else if (num + get_soldados() > 40)
		return 40 - (get_soldados());
	else
		return num;
}
Navio * Galeao::duplica() const {
	return new Galeao(*this);
}

int Galeao::cargaLivre()
{
	return 70 - (peixe + mercadoria);
}

void Galeao::addMercadoria(int quant)
{
	if (quant > cargaLivre())
		mercadoria += cargaLivre();
	else
		mercadoria += quant;
}

void Galeao::addPeixe(int quant)
{
	if (quant > cargaLivre())
		peixe += cargaLivre();
	else
		peixe += quant;
}

int Galeao::maxAgua()
{
	return 400;
}
int Galeao::aguaLivre()
{
	return maxAgua() - get_agua();
}

void Galeao::reageTempestade(){
	set_agua(maxAgua());
	set_soldados((int)(get_soldados() * 0.9));
	if (geraNumero(100) < 40)
	{
		destruir();
	}
}

void Galeao::fazAuto(Jogo * j, int pos, vector <string> & ordens) {
}

void Galeao::tiraPeixe(int a){
	peixe -= a;
}

void Galeao::tiraAgua(int quant)
{
	if (quant <= get_agua())
		set_agua(get_agua() - quant);
}

Galeao::~Galeao()
{
}
