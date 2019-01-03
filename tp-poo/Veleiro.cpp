#include "Veleiro.h"
#include "Jogo.h"

Veleiro::Veleiro(int p, int x, int y, int merc = 0, int fish = 0) : Navio(p, 200, 20, x, y) {
	mercadoria = merc;
	peixe = fish;
	id_cliente = -1;
}

Veleiro::Veleiro(int id, int agua, int sold, int coord_x, int coord_y, bool at, bool mov, int merc, int fish, int preco)
	: Navio(id, agua, sold, coord_x, coord_y, at, mov, preco), mercadoria(merc), peixe(fish) {}

string Veleiro::getAsString(){
	ostringstream oss;

	oss << "Tipo: Veleiro" << "\nId: " << get_id()
		<< "\nPreco: " << get_preco() << "\nQuantidade de agua: " << get_agua()
		<< "\nNumero de soldados: " << get_soldados() << "\nCapacidade: " << getMercadoria() << " (toneladas)"
		<< "\nCoodernadas: " << "{" << get_x() << "," << get_y() << "}"
		<< "\nAtivo: " << isAtivo() << "\nMoveu: " << getMoveu() << endl;

	return oss.str();
}
int Veleiro::isFull(int num) const {
	if (peixe + mercadoria == 40)
		return 0;
	if (peixe + mercadoria + num > 40)
		return 40 - (peixe + mercadoria);
	else 
		return num;
}
int Veleiro::maxSoldados(int num) const {
	if (get_soldados() == 20)
		return 0;
	if (num + get_soldados() > 20)
		return 20 - (get_soldados());
	else
		return num;
}
Navio* Veleiro::duplica() const {
	return new Veleiro(*this);
}

int Veleiro::cargaLivre()
{
	return 40 - (peixe + mercadoria);
}

void Veleiro::addMercadoria(int quant)
{
	if (quant > cargaLivre())
		mercadoria += cargaLivre();
	else
		mercadoria += quant;
}

void Veleiro::addPeixe(int quant)
{
	if (quant > cargaLivre())
		peixe += cargaLivre();
	else
		peixe += quant;
}

int Veleiro::maxAgua()
{
	return 200;
}
int Veleiro::aguaLivre()
{
	return maxAgua() - get_agua();
}

void Veleiro::reageTempestade(){
	set_agua(maxAgua());
	if (cargaLivre() <= 20){
		if (geraNumero(100) < 35)
		{
			destruir();
		}
	}
	else{
		if (geraNumero(100) < 20)
		{
			destruir();
		}
	}
}
void Veleiro::fazAuto(Jogo * j, int id, vector <string> & ordens) { // returns
	int ind = -1;
	auto nav = j->getNavio(id);
	bool inimigo = false;
	if (nav == nullptr) {
		inimigo = true;
		nav = j->getPirata(id);
		if (nav == nullptr){
			return;
		}
	}
	auto cli = j->getNavio(id_cliente);
	// se o veleiro estiver a perseguir uma escuna
	if (id_cliente != -1 && cli != nullptr) {
		coords c_cli;
		c_cli.x = cli->get_x();
		c_cli.y = cli->get_y();
		if (!j->hasPeixe(c_cli.x, c_cli.y))
		{
			nav->set_x(c_cli.x);
			nav->set_y(c_cli.y);
		}
		// se o veleiro tiver capacidade
		if (nav->cargaLivre() == 0)
		{
			id_cliente = -2; // vai para o porto vender
			cli = nullptr;
		}
	}
	// senao
	else if(id_cliente == -1) {
			if (!inimigo)
			{
				for (int i = 0; i < 8 && ind == -1; i++)
					if ((ind = j->procuraAmigos(i, j->pesquisaNavio(id))) != -1) // existe amigo nas redondezas
					{
						auto navA = j->getNavio(ind);
						if (navA->getTipo() == 'E') { // é escuna
							id_cliente = ind;
							coords c;
							c.x = navA->get_x();
							c.y = navA->get_y();
							if (!j->hasPeixe(c.x, c.y)) {
								// se a escuna se mexer
								nav->set_x(c.x);
								nav->set_y(c.y);
							}
						}
					}
					
				if(ind == -1)
				{
					coords destino = j->geraCoordsDestino(j->pesquisaNavio(id));
					if (destino.x == -1 && destino.y == -1)
						return;
					else
					{
						nav->set_x(destino.x);
						nav->set_y(destino.y);
					}
				}
			}
			else
			{
				coords destino = j->geraCoordsDestinoPirata(j->pesquisaPiratas(id));
				if (destino.x == -1 && destino.y == -1)
					return;
				else
				{
					nav->set_x(destino.x);
					nav->set_y(destino.y);
				}
			}
	}
	else
	{
		//string s = "vaipara ";
		//s += id; s += j->portoPrincipal()->getID();
		//ordens.push_back(s);
	}
}

void Veleiro::tiraPeixe(int a) {
	peixe -= a;
}

void Veleiro::tiraAgua(int quant)
{
	if(quant <=get_agua())
	set_agua(get_agua()-quant);
}

Veleiro::~Veleiro()
{
}