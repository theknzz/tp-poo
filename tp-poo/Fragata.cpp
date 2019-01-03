 
#include "Fragata.h"
#include "Jogo.h"

Fragata::Fragata(int p, int x, int y) : Navio(p, 500, 50, x, y) {

}
Fragata::Fragata(int id, int agua, int sold, int coord_x, int coord_y, bool at, bool mov, int preco) :
	Navio(id, agua, sold, coord_x, coord_y, at, mov, preco) {}

string Fragata::getAsString(){
	ostringstream oss;

	oss << "Tipo: Fragata" << "\nId: " << get_id()
		<< "\nPreco: " << get_preco() << "\nQuantidade de agua: " << get_agua()
		<< "\nNumero de soldados: " << get_soldados() << "\nCoodernadas : " << "{" << get_x() << "," << get_y() << "}" << endl;

	return oss.str();
}
int Fragata::isFull(int num) const {
	return -1;
}
Navio * Fragata::duplica() const {
	return new Fragata(*this);
}
void Fragata::fazAuto(Jogo * j, int id, vector <string> &ordens) {
	bool inimigo = false;
	int ind = -1;
	auto nav = j->getNavio(id);
	if (nav == nullptr) {
		inimigo = true;
		nav = j->getPirata(id);
		if (nav == nullptr){
			return;
		}
	}
	if (!inimigo) { // sou amigo
		for(int i = 0 ; i < 8; i++)
			if (ind = j->procuraInimigos(i, j->pesquisaNavio(id)) != -1)
			{
				// encontrei um inimigo
				// vou andar atras dele
				auto navA = j->getPirata(ind);
				// considerando que os navios piratas
				// andam em todos os turnos
				nav->set_x(navA->get_x());
				nav->set_y(navA->get_y());
			}
		if (id_protege != -1)
		{
			auto cover = j->getNavio(id_protege);
			if (cover->getTipo() != 'S' && cover->getTipo() != 'G')
			{
				nav->set_x(cover->get_x());
				nav->set_y(cover->get_y());
			}
		}
		else
			for (int i = 0; i < 8; i++) {
				ind = j->procuraAmigos(i, j->pesquisaNavio(id));
				if (ind != -1)
				{
					auto amg = j->getNavio(ind);
					id_protege = ind;
					if (amg->getTipo() != 'G' && amg->getTipo() != 'S') {
						nav->set_x(amg->get_x());
						nav->set_y(amg->get_y());
					}
				}
			}

				if(ind == -1)
				{
					coords d = j->geraCoordsDestino(j->pesquisaNavio(id));
					if (d.x == -1 && d.y == -1)
						return;
					else
					{
						nav->set_x(d.x);
						nav->set_y(d.y);
					}
				}
	}
	else // se sou inimigo
	{
		coords d = j->geraCoordsDestinoPirata(j->pesquisaPiratas(id));
		if (d.x == -1 && d.y == -1)
			return;
		else
		{
			nav->set_x(d.x);
			nav->set_y(d.y);
		}
	}
}

int Fragata::cargaLivre()
{
	return 0;
}
int Fragata::aguaLivre()
{
	return maxAgua() - get_agua();
}
void Fragata::addMercadoria(int quant)
{
	return;
}

void Fragata::addPeixe(int quant)
{
	return;
}

int Fragata::maxAgua()
{
	return 500;
}

int Fragata::maxSoldados(int num) const {
	if (get_soldados() == 50)
		return 0;
	else if (num + get_soldados() > 50)
		return 50 - (get_soldados());
	else
		return num;
}

void Fragata::reageTempestade()
{
	set_agua(maxAgua());
	if (geraNumero(100) < 20)
		destruir();
	set_soldados((int)(get_soldados() * 0.85));
}

void Fragata::tiraAgua(int quant)
{
	if (quant <= get_agua())
		set_agua(get_agua() - quant);
}

Fragata::~Fragata()
{
}
