#include "Navio.h"
//#include "Jogo.h"
#include "Veleiro.h"
#include "Escuna.h"
#include "Galeao.h"
#include "Fragata.h"
#include "Config.h"
#include "Especial.h"
#include "Porto.h"

using namespace std;

int Navio::conta = 0;


Navio::Navio(int p, int qt, int nr, int coord_x, int coord_y)
	:preco(p), qt_agua(qt), nr_soldados(nr)
{
	coord.x = coord_x;
	coord.y = coord_y;
	id = ++conta;
}
Navio::Navio(int id_novo, int agua, int sold, int x, int y, bool at, bool mov, int preco_c)
	:id(id_novo), qt_agua(agua), nr_soldados(sold), ativo(at), moveu(mov), preco(preco_c)
{
	coord.x = x;
	coord.y = y;
}
void Navio::set_preco(int p)
{
	preco = p;
}
void Navio::set_agua(int qt)
{
	qt_agua = qt;
}
void Navio::set_soldados(int nr)
{
	if (nr < 0)
		nr_soldados = 0;
	else
		nr_soldados = nr;
}
void Navio::set_x(const int coord_x)
{
	coord.x = coord_x;
}
void Navio::set_y(const int coord_y)
{
	coord.y = coord_y;
}

void Navio::destruir()
{
	ativo = false;
}

int Navio::addAgua(int quant)
{
	if (quant > maxAgua())
	{
		qt_agua += aguaLivre();
		return aguaLivre();
	}
	else
		qt_agua += quant;
	return quant;
}

bool Navio::isAtivo()
{
	return ativo;
}

Navio * Navio::fabrica(char tipo, Config cfg, Porto * p) {
	if (tipo == 'V') {
		return new Veleiro(cfg.precoveleiro, p->get_x(), p->get_y(), 0, 0);
	}
	if (tipo == 'F') {
		return new Fragata(cfg.precofragata, p->get_x(), p->get_y());
	}
	if (tipo == 'G') {
		return new Galeao(cfg.precogaleao, p->get_x(), p->get_y(), 0, 0);
	}
	if (tipo == 'E') {
		return new Escuna(cfg.precoescuna, p->get_x(), p->get_y(), 0, 0);
	}
	if (tipo == 'S') {
		return new Especial(cfg.precoespecial, p->get_x(), p->get_y());
	}
	return nullptr;
}
Navio * Navio::fabrica(int x, int y, char tipo, Config cfg) {
	if (tipo == 'V') {
		return new Veleiro(cfg.precoveleiro, x, y, 0, 0);
	}
	if (tipo == 'F') {
		return new Fragata(cfg.precofragata, x, y);
	}
	return nullptr;
}

Navio::~Navio()
{
}

