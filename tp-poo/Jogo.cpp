#include "Jogo.h"
#include "Porto.h"
#include "Escuna.h"
#include "Especial.h"
#include "Fragata.h"
#include "Galeao.h"
#include "Veleiro.h"
#include "Celula.h"
#include "Evento.h"
#include "Consola.h"

#include <time.h>
#include <cstdio>
#include <sstream>
#include <iostream>
using namespace std;

Jogo::Jogo(Jogador * player, int d) {
	jogador = player;
	dificuldade = d;
}

bool Jogo::le_fich(string nome_fich) {
	char ch;
	string str;
	int max_portos;

	ifstream fich(nome_fich);

	if (!fich.is_open()) {
		return false;
	}

	for (auto i = 0; i < 2; i++)
	{
		getline(fich, str);
		istringstream iss(str);
		iss >> str;
		if (str == "linhas")
			iss >> config.linhas;
		else
			iss >> config.colunas;
	}
	for (auto i = 0; i < config.linhas; i++)
	{
		for (auto j = 0; j < config.colunas; j++)
		{
			fich >> ch;
			if (ch != '.' && ch != '+')
			{
					Porto * pt = new Porto('?', j, i);
					portosInimigos.push_back(pt);
					Celula a(j, i, 'p', pt);
					mapa.push_back(a);
			}
			else
			{
				Celula a(j, i, ch);
				mapa.push_back(a);
			}
		}
	}
	// apanhar o enter
	getline(fich, str);

	while (!fich.eof())
	{
		getline(fich, str);
		istringstream le(str);
		if (le >> str)
			var(str, le, config);
	}
	fich.close();
	jogador->setMoedas(config.moedas); 
	if (dificuldade == 1) {
		max_portos = ceil(portosInimigos.size() / 2);
	}
	else
		max_portos = 1;
	for (int i = 0; i < max_portos; i++) {
		int x = geraNumero(portosInimigos.size());
		Porto * p = portosInimigos[x];
		portosInimigos.erase(portosInimigos.begin() + x);
		p->setID(toupper(p->getID()));
		portos.push_back(p);
	}
	return true;
}
void Jogo::mostra_mapa() {
	int cor;
	bool claro, tipoCor = 0; //cor guarda a Consola::(static const int) || tipoCor =0 em linhas impares, e =1 em linhas pares
	int a, l, i, j;

	Consola::clrscr();
	Consola::setTextColor(Consola::BRANCO_CLARO);
	for (a = 0; a < config.linhas; a++) {
		if (tipoCor == 0)  //define a primeira cor a usar na linha, tendo em conta se e par ou impar
			claro = 0;
		else
			claro = 1;
		for (i = 0; i < 2; i++) {						//prepara para escrever a mesma linha 2x, uma vez que cada celula e representada em 2x2
			for (l = 0; l < config.colunas; l++) {

				if (mapa[a*config.colunas + l].getTipo() == '.')
				{
					if (claro == 0)
						cor = Consola::AZUL;
					else
						cor = Consola::AZUL_CLARO;
				}
				else if (mapa[a*config.colunas + l].getTipo() == '+') {
					if (claro == 0)
						cor = Consola::VERDE;
					else
						cor = Consola::VERDE_CLARO;
				}
				else {
					if (claro == 0)
						cor = Consola::VERMELHO;
					else
						cor = Consola::VERMELHO_CLARO;
				}
				Consola::setBackgroundColor(cor);
				for (j = 0; j < 2; j++) {				//prepara para escrever a mesma celula 2x, uma vez que cada celula e representada em 2x2
					if (mapa[a*config.colunas + l].isPorto())
						cout << mapa[a*config.colunas + l].getPorto()->getID();
					else
						cout << mapa[a*config.colunas + l].getTipo();
				}
				if (claro == 0) {		//troca a cor, para fazer padrao xadrez durante a linha
					claro = 1;
				}
				else {
					claro = 0;
				}
			}
			Consola::setBackgroundColor(Consola::PRETO);
			Consola::setTextColor(Consola::PRETO);
			cout << '|' << endl;
			Consola::setTextColor(Consola::BRANCO_CLARO);
		}
		if (tipoCor == 0) //troca tipoCor, o que definira a cor inicial da proxima linha para manter padrao xadrez
			tipoCor = 1;
		else
			tipoCor = 0;
	}
	Consola::setBackgroundColor(Consola::PRETO);
	Consola::setTextColor(Consola::BRANCO);
}

void Jogo::mostra_navios() {
	for (int i = 0; i < getSizeNavios(); i++) {
		Consola::gotoxy(getNavX(i) * 2, getNavY(i) * 2 + 1);
		if ((getNavX(i) + getNavY(i)) % 2 == 0) {
			if (mapa[config.colunas*getNavY(i) + getNavX(i)].getTipo() == '.')
				Consola::setBackgroundColor(Consola::AZUL);
			else
				Consola::setBackgroundColor(Consola::VERMELHO);
		}
		else {
			if (mapa[config.colunas*getNavY(i) + getNavX(i)].getTipo() == '.')
				Consola::setBackgroundColor(Consola::AZUL_CLARO);
			else
				Consola::setBackgroundColor(Consola::VERMELHO_CLARO);
		}
		Consola::setBackgroundColor(Consola::AMARELO_CLARO);
		cout << getNavId(i);
	}
	for (int i = 0; i < getSizeNaviosInimigos(); i++) {
		Consola::gotoxy(getNavInimX(i) * 2, getNavInimY(i) * 2 + 1);
		if ((getNavInimX(i) + getNavInimY(i)) % 2 == 0) {
			if (mapa[config.colunas*getNavInimY(i) + getNavInimX(i)].getTipo() == '.')
				Consola::setBackgroundColor(Consola::AZUL);
			else
				Consola::setBackgroundColor(Consola::VERMELHO);
		}
		else {
			if (mapa[config.colunas*getNavInimY(i) + getNavInimX(i)].getTipo() == '.')
				Consola::setBackgroundColor(Consola::AZUL_CLARO);
			else
				Consola::setBackgroundColor(Consola::VERMELHO_CLARO);
		}
		Consola::setBackgroundColor(Consola::ROXO);
		cout << getNavInimId(i);
	}
	for (unsigned int i = 0; i < naviosDeriva.size(); i++) {
		Consola::gotoxy(naviosDeriva[i]->get_x() * 2, naviosDeriva[i]->get_y() * 2 + 1);
		if ((naviosDeriva[i]->get_x() + naviosDeriva[i]->get_y()) % 2 == 0) {
			if (mapa[config.colunas*naviosDeriva[i]->get_y() + naviosDeriva[i]->get_x()].getTipo() == '.')
				Consola::setBackgroundColor(Consola::AZUL);
			else
				Consola::setBackgroundColor(Consola::VERMELHO);
		}
		else {
			if (mapa[config.colunas*naviosDeriva[i]->get_y() + naviosDeriva[i]->get_x()].getTipo() == '.')
				Consola::setBackgroundColor(Consola::AZUL_CLARO);
			else
				Consola::setBackgroundColor(Consola::VERMELHO_CLARO);
		}
		Consola::setBackgroundColor(Consola::BRANCO_CLARO);
		cout << naviosDeriva[i]->get_id();
	}
	Consola::gotoxy(0, config.linhas * 2);
	Consola::setBackgroundColor(Consola::PRETO);
}

int Jogo::jog_getmoedas()
{
	return jogador->getMoedas();
}
int Jogo::conf_getpreconavios()
{
	return config.preconavio;
}
int Jogo::pesquisaNavio(const int num) const
{
	for (unsigned int i = 0; i < navios.size(); i++)
		if (navios[i]->get_id() == num) {
			return i;
		}
	return -1; // nao existe navio com id = num
}
int Jogo::pesquisaPiratas(const int num) const
{
	for (unsigned int i = 0; i < naviosInimigos.size(); i++)
		if (naviosInimigos[i]->get_id() == num) {
			return i;
		}
	return -1; // nao existe navio pirata com id = num
}
bool Jogo::isAgua(int x, int y) {
	if (mapa[y*config.colunas + x].getTipo() == '.')
		return true;
	return false;
}
bool Jogo::isTerra(int x, int y) {
	if (mapa[y*config.colunas + x].getTipo() == '+')
		return true;
	return false;
}
bool Jogo::isPortoAmigo(int x, int y) {
	// se as coordenadas nao apontarem para um porto
	// e este nao for amigo
	if (!mapa[y*config.colunas + x].isPorto() || isupper(mapa[y*config.colunas + x].getPorto()->getID()) == 0) {
		return false;
	}
	return true;
}
bool Jogo::isOcupado(int x, int y) {
	for (unsigned int i = 0; i < navios.size(); i++) 
		if (navios[i]->get_x() == x && navios[i]->get_y() == y)
			return true;
	for(unsigned int j = 0; j < naviosInimigos.size(); j++)
		if (naviosInimigos[j]->get_x() == x && naviosInimigos[j]->get_y() == y)
			return true;
	for (unsigned int j = 0; j < naviosDeriva.size(); j++)
		if (naviosDeriva[j]->get_x() == x && naviosDeriva[j]->get_y() == y)
			return true;
	return false;
}
bool Jogo::moveNavio(int id, string key) {
	coords coords;
	int qual = pesquisaNavio(id);
	if (qual == -1)
		return false;
	if (navios[qual]->getMoveu())
		return false;
	coords.x = navios[qual]->get_x();
	coords.y = navios[qual]->get_y();
	if (key == "D") { // direita
		coords = semFronteiras(coords.x + 1, coords.y);
		if (canMoveNavio(coords.x, coords.y, qual))
		{
			navios[qual]->set_x(coords.x);
			navios[qual]->setMoveu(true);
			return true;
		}
		return false;
	}
	else if (key == "E") { // esquerda
		coords = semFronteiras(coords.x - 1, coords.y);
		if (canMoveNavio(coords.x, coords.y, qual)) {
			navios[qual]->set_x(coords.x);
			navios[qual]->setMoveu(true);
			return true;
		}
		return false;
	}
	else if (key == "C") { // cima
		coords = semFronteiras(coords.x, coords.y - 1);
		if (canMoveNavio(coords.x, coords.y, qual))
		{
			navios[qual]->set_y(coords.y);
			navios[qual]->setMoveu(true);
			return true;
		}
		return false;
	}
	else if (key == "B") { // baixo
		coords = semFronteiras(coords.x, coords.y + 1);
		if (canMoveNavio(coords.x, coords.y, qual)) {
			navios[qual]->set_y(coords.y);
			navios[qual]->setMoveu(true);
			return true;
		}
		return false;
	}
	else if (key == "CE") { // cima + esquerda
		coords = semFronteiras(coords.x - 1, coords.y - 1);
		if (canMoveNavio(coords.x, coords.y, qual)) {
			navios[qual]->set_y(coords.y);
			navios[qual]->set_x(coords.x);
			navios[qual]->setMoveu(true);
			return true;
		}
		return false;
	}
	else if (key == "CD") { // cima + direita
		coords = semFronteiras(coords.x + 1, coords.y - 1);
		if (canMoveNavio(coords.x, coords.y, qual)) {
			navios[qual]->set_y(coords.y);
			navios[qual]->set_x(coords.x);
			navios[qual]->setMoveu(true);
			return true;
		}
		return false;
	}
	else if (key == "BE") { // baixo + esquerda
		coords = semFronteiras(coords.x - 1, coords.y + 1);
		if (canMoveNavio(coords.x, coords.y, qual)) {
			navios[qual]->set_y(coords.y);
			navios[qual]->set_x(coords.x);
			navios[qual]->setMoveu(true);
			return true;
		}
		return false;
	}
	else if (key == "BD") { // baixo + direita
		coords = semFronteiras(coords.x + 1, coords.y + 1);
		if (canMoveNavio(coords.x, coords.y, qual)) {
			navios[qual]->set_y(coords.y);
			navios[qual]->set_x(coords.x);
			navios[qual]->setMoveu(true);
			return true;
		}
		return false;
	}
	return false;
}
void Jogo::adicionaMoedas(int num) {
	jogador->setMoedas(jogador->getMoedas() + num);
}
void Jogo::removeMoedas(int num) {
	jogador->setMoedas(jogador->getMoedas() - num);
}
int Jogo::precoNavio(char tipo) {
	if (tipo == 'E')
		return config.precoescuna;
	if (tipo == 'V')
		return config.precoveleiro;
	if (tipo == 'G')
		return config.precoveleiro;
	if (tipo == 'F')
		return config.precofragata;
	if (tipo == 'S')
		return config.precoespecial;
	return -1;
}
bool Jogo::compraNavio(char tipo) {
	if(portoPrincipal() != nullptr) {
		if (jogador->getMoedas() >= precoNavio(tipo)) {
			Navio * p = Navio::fabrica(tipo, config, portoPrincipal());
			if (p == nullptr)
				return false;
			removeMoedas(precoNavio(tipo));
			navios.push_back(p);
			return true;
		}
	}
	return false;
}
bool Jogo::acrescentaNavioPirata(int x, int y, char tipo) {
	if (!isAgua(x, y) || isOcupado(x,y))
		return false;
	Navio *p = Navio::fabrica(x, y, tipo, config);
	if (p == nullptr)
		return false;
	naviosInimigos.push_back(p);
	return true;
}
bool Jogo::compraMercadoria(int id, int num) {
	int value;
	int qual = pesquisaNavio(id);
	if (qual == -1 || navios[qual]->getMercadoria() == -1)
		return false;
	// quant = quantidade que se pode comprar
	int quant = navios[qual]->isFull(num);
	if (quant == 0)
		return false;
	for (unsigned int i = 0; i < portos.size(); i++)
	{
		if (portos[i]->get_x() == navios[qual]->get_x() && portos[i]->get_y() == navios[qual]->get_y()) {
			// se a quantidade que o user pediu poder ser comprada
			if (quant == num)
				value = quant * config.precocompmercad;
			// senao
			else if (quant < num || quant != 0)
				// no caso de nao ser possivel comprar
				// toda a mercadoria desejada
				value = quant * config.precocompmercad;
			if (jogador->getMoedas() > value) {
				removeMoedas(value);
				navios[qual]->setMercadoria(navios[qual]->getMercadoria() + quant);
				return true;
			}
		}
	}
	return false;
}
bool Jogo::vendeMercadoria(int id) {
	int qual = pesquisaNavio(id);
	if (qual == -1)
		return false;
	for(unsigned int i=0;i<portos.size();i++)
	{
		if(portos[i]->get_x()==navios[qual]->get_x() && portos[i]->get_y() == navios[qual]->get_y())
		{
			int value;
			value = (navios[qual]->getMercadoria() * config.precovendmercad) + (navios[qual]->get_soldados() * config.precosoldado);
			navios[qual]->setMercadoria(0);
			navios[qual]->set_soldados(0);
			adicionaMoedas(value);
			return true;
		}
	}
	return false;
}
bool Jogo::vendeNavio(int id) {
	int qual = pesquisaNavio(id);
	if (qual == -1)
		return false;
	// so vende se estiver num porto amigo
	if (isPortoAmigo(navios[qual]->get_x(), navios[qual]->get_y()))	{
		// entao vende mercadoria
		vendeMercadoria(qual);
		// vende o navio
		adicionaMoedas(precoNavio( navios[qual]->getTipo() ));
		// depois de vendido o navio � retirado ao jogador
		delete navios[qual];
		navios.erase(navios.begin() + qual);
		return true;
	}
	return false;
}
bool Jogo::compraSoldados(int id, int num) {
	int value, quant;
	int qual = pesquisaNavio(id);
	if (qual == -1)
		return false;
	quant = navios[qual]->maxSoldados(num);
	if (quant == 0)
		return false;
	for (unsigned  i = 0; i < portos.size(); i++)
	{
		if (portos[i]->get_x() == navios[qual]->get_x() && portos[i]->get_y() == navios[qual]->get_y()) {
			if (quant == num)
				value = quant * config.precosoldado;
			else if (quant < num)
				value = quant * config.precosoldado;
			if (jogador->getMoedas() > value) {
				removeMoedas(value);
				navios[qual]->set_soldados(navios[qual]->get_soldados() + quant);
				return true;
			}
		}
	}
	return false;
}
Navio* Jogo::getNavio(int num) const{
	int qual = pesquisaNavio(num);
	if (qual != -1)
		return navios[qual];
	else
		return nullptr;
}
Navio * Jogo::getPirata(int num) const {
	int qual = pesquisaPiratas(num);
	if (qual != -1)
		return naviosInimigos[qual];
	else
		return nullptr;
}
Navio * Jogo:: getNaviobyPos(int p) const {
	if(p < navios.size() && p >= 0)
		return navios[p];
	return nullptr;
}
Navio * Jogo::getPiratabyPos(int p) const {
	if (p < naviosInimigos.size() && p >= 0)
		return naviosInimigos[p];
	return nullptr;
}
int Jogo::getNavInimId(int i) {
	return naviosInimigos[i]->get_id();
}
int Jogo::getxEvento() const {
	return evento->get_x();
}
Evento * Jogo::getEvento() const {
	return evento;
}
int Jogo::getNavId(int i) {
	return navios[i]->get_id();
}

int Jogo::getNavInimX(int i) {
	return naviosInimigos[i]->get_x();
}

int Jogo::getNavInimY(int i) {
	return naviosInimigos[i]->get_y();
}

int Jogo::getNavX(int i) {
	return navios[i]->get_x();
}

int Jogo::getNavY(int i) {
	return navios[i]->get_y();
}

void Jogo::mostraNavios() const {
	cout << "\nmostra navios " << endl;
	for (unsigned int i = 0; i < navios.size(); i++)
		cout << navios[i]->getAsString() << endl;
}
Porto * Jogo::portoPrincipal() {
	if(portos.size() != 0)
		return portos[0];
	return nullptr;
}
void Jogo::mostraPortos() const {
	cout << "\nmostra portos: " << endl;
	for (unsigned int i = 0; i < portos.size(); i++)
		cout << portos[i]->getAsString() << endl;
}
void Jogo::mostraNaviosInimigos() const {
	cout << "\nmostra navios inimigos" << endl;
	for (unsigned int i = 0; i < naviosInimigos.size(); i++)
		cout << naviosInimigos[i]->getAsString() << endl;
}


bool Jogo::canMoveNavio(int x, int y, int qual) {
	if ((isAgua(x,y) || isPortoAmigo(x,y)) && !isOcupado(x,y))
		return true;
	return false;
}
int Jogo::pontuacao() {
	int pont = 0;
	for (unsigned int i = 0; i < navios.size(); i++) 
		pont += navios[i]->getMercadoria() * config.precovendmercad + navios[i]->get_soldados() * config.precosoldado + precoNavio(navios[i]->getTipo());
	pont += jog_getmoedas();
	return pont;
}
coords Jogo::semFronteiras(int x, int y) {
	coords coords;
	coords.x = x;
	coords.y = y;
	// limite � direita
	if (x > config.colunas - 1)
		coords.x = x - ((int)(x / config.colunas))*config.colunas;       //  6  -  ((int)(6/4)) * 4  -->  6 - 1*4  -->  2    ,  config.colunas = 4
	// limite � esquerda
	else if (x < 0)
		coords.x = x + (((int)(-x / config.colunas)) + 1)*config.colunas;   // -7  +  ( (  (int)(7/4)  )  +1 ) * 4  -->  -7  +  (1+1) * 4   -->  -7 + 2*4  -->  -7 + 8  --> 1   , com config.colunas=4
	// limite para baixo
	if (y > config.linhas - 1)
		coords.y = y - ((int)(y / config.linhas))*config.linhas;
	// limite para cima
	else if (y < 0)
		coords.y = y + (((int)(-y/ config.linhas)) + 1)*config.linhas;
	return coords;
}
bool Jogo::hasPeixe(int x, int y) {
	if (mapa[y*config.colunas + x].getPeixe() == 1)
		return true;
	return false;
}
bool Jogo::hasNavio(int x, int y) {
	coords coords;
	for(unsigned int i = 0; i < navios.size(); i++) {
		coords.x = navios[i]->get_x();
		coords.y = navios[i]->get_y();
		if (coords.x == x && coords.y == y)
			return true;
	}
	return false;
}
coords Jogo::maisPerto(coords atual,int x, int y, int cel) {
	coords coords, ideal, test;
	float menor = FLT_MAX, aux;
	coords.x = x; coords.y = y;
	test = atual;
	for (int i = 0; i < 8; i++, atual = test)
		switch (i) {
			case 1: // CE
				atual = semFronteiras(atual.x - cel, atual.y - cel);
				if (isTerra(atual.x, atual.y) || isOcupado(atual.x, atual.y))
					break;
				aux = hipotenusa(atual, coords);
				if (aux < menor) {
					menor = aux;
					ideal = atual;
				}
				break;
			case 2: // CD
				atual = semFronteiras(atual.x + cel, atual.y - cel);
				if (isTerra(atual.x, atual.y) || isOcupado(atual.x, atual.y))
					break;
				aux = hipotenusa(atual, coords);
				if (aux < menor) {
					menor = aux;
					ideal = atual;
				}
				break;
			case 3: // BE
				atual = semFronteiras(atual.x - cel, atual.y + cel);
				if (isTerra(atual.x, atual.y) || isOcupado(atual.x, atual.y))
					break; 
				aux = hipotenusa(atual, coords);
				if (aux < menor) {
					menor = aux;
					ideal = atual;
				}
				break;
			case 4: // BD
				atual = semFronteiras(atual.x + cel, atual.y + cel);
				if (isTerra(atual.x, atual.y) || isOcupado(atual.x, atual.y))
					break;
				aux = hipotenusa(atual, coords);
				if (aux < menor) {
					menor = aux;
					ideal = atual;
				}
				break;
			case 5: // E
				atual = semFronteiras(atual.x - cel, atual.y);
				if (isTerra(atual.x, atual.y) || isOcupado(atual.x, atual.y))
					break;
				aux = hipotenusa(atual, coords);
				if (aux < menor) {
					menor = aux;
					ideal = atual;
				}
				break;
			case 6: // D
				atual = semFronteiras(atual.x + cel, atual.y);
				if (isTerra(atual.x, atual.y) || isOcupado(atual.x, atual.y))
					break;
				aux = hipotenusa(atual, coords);
				if (aux < menor) {
					menor = aux;
					ideal = atual;
				}
				break;
			case 7: // B
				atual = semFronteiras(atual.x, atual.y + cel);
				if (isTerra(atual.x, atual.y) || isOcupado(atual.x, atual.y))
					break;
				aux = hipotenusa(atual, coords);
				if (aux < menor) {
					menor = aux;
					ideal = atual;
				}
				break;
			case 8: // C
				atual = semFronteiras(atual.x, atual.y - cel);
				if (isTerra(atual.x, atual.y) || isOcupado(atual.x, atual.y))
					break;
				aux = hipotenusa(atual, coords);
				if (aux < menor) {
					menor = aux;
					ideal = atual;
				}
				break;
		} // switch
	return ideal;
}

int geraNumero(int x) {
	if (x == 0)
		return 0;
	return rand() % x;
}

int Jogo::procuraInimigos(int t, int i) {
	coords c;
	switch(t)
	{
	case 0:
		c = semFronteiras(navios[i]->get_x() - 1, navios[i]->get_y() - 1);
		break;
	case 1:
		c = semFronteiras(navios[i]->get_x(), navios[i]->get_y() - 1);
		break;
	case 2:
		c = semFronteiras(navios[i]->get_x() + 1, navios[i]->get_y() - 1);
		break;
	case 3:
		c = semFronteiras(navios[i]->get_x() - 1, navios[i]->get_y());
		break;
	case 4:
		c = semFronteiras(navios[i]->get_x() + 1, navios[i]->get_y());
		break;
	case 5:
		c = semFronteiras(navios[i]->get_x() - 1, navios[i]->get_y() + 1);
		break;
	case 6:
		c = semFronteiras(navios[i]->get_x(), navios[i]->get_y() + 1);
		break;
	case 7:
		c = semFronteiras(navios[i]->get_x() + 1, navios[i]->get_y() + 1);
		break;
	}
	for (unsigned int j = 0; j < naviosInimigos.size(); j++) {
		if (c.x == naviosInimigos[j]->get_x() && c.y == naviosInimigos[j]->get_y() && naviosInimigos[j]->isAtivo())
		{
			return j;
		}
	}
	return -1;
}
int Jogo::procuraInimigosDeriva(int t, int i) {
	coords c;
	switch (t)
	{
	case 0:
		c = semFronteiras(naviosDeriva[i]->get_x() - 1, naviosDeriva[i]->get_y() - 1);
		break;
	case 1:
		c = semFronteiras(naviosDeriva[i]->get_x(), naviosDeriva[i]->get_y() - 1);
		break;
	case 2:
		c = semFronteiras(naviosDeriva[i]->get_x() + 1, naviosDeriva[i]->get_y() - 1);
		break;
	case 3:
		c = semFronteiras(naviosDeriva[i]->get_x() - 1, naviosDeriva[i]->get_y());
		break;
	case 4:
		c = semFronteiras(naviosDeriva[i]->get_x() + 1, naviosDeriva[i]->get_y());
		break;
	case 5:
		c = semFronteiras(naviosDeriva[i]->get_x() - 1, naviosDeriva[i]->get_y() + 1);
		break;
	case 6:
		c = semFronteiras(naviosDeriva[i]->get_x(), naviosDeriva[i]->get_y() + 1);
		break;
	case 7:
		c = semFronteiras(naviosDeriva[i]->get_x() + 1, naviosDeriva[i]->get_y() + 1);
		break;
	}
	for (unsigned int j = 0; j < naviosInimigos.size(); j++) {
		if (c.x == naviosInimigos[j]->get_x() && c.y == naviosInimigos[j]->get_y() && naviosInimigos[j]->isAtivo())
		{
			return j;
		}
	}
	return -1;
}
int Jogo::procuraAmigos(int t, int i) {
	coords c;
	switch (t)
	{
	case 0:
		c = semFronteiras(navios[i]->get_x() - 1, navios[i]->get_y() - 1);
		break;
	case 1:
		c = semFronteiras(navios[i]->get_x(), navios[i]->get_y() - 1);
		break;
	case 2:
		c = semFronteiras(navios[i]->get_x() + 1, navios[i]->get_y() - 1);
		break;
	case 3:
		c = semFronteiras(navios[i]->get_x() - 1, navios[i]->get_y());
		break;
	case 4:
		c = semFronteiras(navios[i]->get_x() + 1, navios[i]->get_y());
		break;
	case 5:
		c = semFronteiras(navios[i]->get_x() - 1, navios[i]->get_y() + 1);
		break;
	case 6:
		c = semFronteiras(navios[i]->get_x(), navios[i]->get_y() + 1);
		break;
	case 7:
		c = semFronteiras(navios[i]->get_x() + 1, navios[i]->get_y() + 1);
		break;
	}
	for (unsigned int j = 0; j < navios.size(); j++) {
		if (c.x == navios[j]->get_x() && c.y == navios[j]->get_y() && navios[j]->isAtivo())
		{
			return j;
		}
	}
	return -1;
}
int Jogo::procuraAmigosDeriva(int t, int i) {
	coords c;
	switch (t)
	{
	case 0:
		c = semFronteiras(naviosDeriva[i]->get_x() - 1, naviosDeriva[i]->get_y() - 1);
		break;
	case 1:
		c = semFronteiras(naviosDeriva[i]->get_x(), naviosDeriva[i]->get_y() - 1);
		break;
	case 2:
		c = semFronteiras(naviosDeriva[i]->get_x() + 1, naviosDeriva[i]->get_y() - 1);
		break;
	case 3:
		c = semFronteiras(naviosDeriva[i]->get_x() - 1, naviosDeriva[i]->get_y());
		break;
	case 4:
		c = semFronteiras(naviosDeriva[i]->get_x() + 1, naviosDeriva[i]->get_y());
		break;
	case 5:
		c = semFronteiras(naviosDeriva[i]->get_x() - 1, naviosDeriva[i]->get_y() + 1);
		break;
	case 6:
		c = semFronteiras(naviosDeriva[i]->get_x(), naviosDeriva[i]->get_y() + 1);
		break;
	case 7:
		c = semFronteiras(naviosDeriva[i]->get_x() + 1, naviosDeriva[i]->get_y() + 1);
		break;
	}
	for (unsigned int j = 0; j < navios.size(); j++) {
		if (c.x == navios[j]->get_x() && c.y == navios[j]->get_y() && navios[j]->isAtivo())
		{
			return j;
		}
	}
	return -1;
}


float Jogo::hipotenusa(coords a, coords b) {
	int x, y;
	x = a.x - b.x;
	y = a.y - b.y;
	return sqrt(pow(x, 2) + pow(y, 2));
}
bool Jogo::isDestino(int x, int y, coords destino) {
	if (destino.x == x && destino.y == y)
		return true;
	return false;
}
bool Jogo::vaiparacoords(int id, int x, int y) {
	coords destino, partida, check;
	int qtdCelulas;
	check.x = x; check.y = y;
	int qual = pesquisaNavio(id);
	if (qual == -1 || navios[qual]->getMoveu() || isTerra(x,y) || isOcupado(x,y))
		return false;
	// calcular quantas celulas o navio vai andar
	qtdCelulas = navios[qual]->ando();
	for(int i = 0 ; i < qtdCelulas; i++) {
		partida.x = navios[qual]->get_x();
		partida.y = navios[qual]->get_y();
		if(!isDestino(navios[qual]->get_x(), navios[qual]->get_y(), check)){
			destino = maisPerto(partida, x, y, 1);
			navios[qual]->set_x(destino.x);
			navios[qual]->set_y(destino.y);
		}
	}
	navios[qual]->setMoveu(true);
	return isDestino(navios[qual]->get_x(), navios[qual]->get_y(), check);
}
bool Jogo::vaiparaporto(int id, char c) {
	coords p;
	p = procuraPorto(c);
	return vaiparacoords(id, p.x, p.y);
}

coords Jogo::procuraPorto(char c) {
	coords q;
	for (unsigned int i = 0; i < portos.size(); i++) {
		if (portos[i]->getID() == c){
			q.x = portos[i]->get_x();
			q.y = portos[i]->get_y();
			return q;
		}
	}
	for (unsigned int i = 0; i < portosInimigos.size(); i++) {
		if (portosInimigos[i]->getID() == c) {
			q.x = portosInimigos[i]->get_x();
			q.y = portosInimigos[i]->get_y();
			return q;
		}
	}
	q.x = -1;
	q.y = -1;
	return q;
}

bool Jogo::batalha(int i, int j)
{
	if (j == -1)
		return false;
	int sold = navios[i]->get_soldados();
	int sold_i = naviosInimigos[j]->get_soldados();
	int poder_navio = geraNumero(sold);
	int poder_inimigo = geraNumero(sold_i);
	if(poder_navio > poder_inimigo){
		int reducao = ceil(sold*0.2);
		navios[i]->set_soldados(sold - reducao);
		naviosInimigos[j]->set_soldados(sold_i - (reducao * 2));
	}
	else{
		int reducao = ceil(sold_i*0.2);
		naviosInimigos[i]->set_soldados(sold_i - reducao);
		navios[j]->set_soldados(sold - (reducao * 2));
	}
	if (naviosInimigos[j]->get_soldados() == navios[i]->get_soldados() == 0)
	{
		naviosInimigos[j]->destruir();
		navios[i]->destruir();
	}
	else if (naviosInimigos[j]->get_soldados() == 0) {
		int merc = naviosInimigos[j]->getMercadoria() / 2;
		navios[i]->addMercadoria(merc);
		int peixe = naviosInimigos[j]->getPeixe();
		navios[i]->addPeixe(peixe);
		navios[i]->addAgua(naviosInimigos[j]->get_agua());
		naviosInimigos[j]->destruir();
	}
	else if (navios[i]->get_soldados() == 0)
	{
		int merc = navios[i]->getMercadoria() / 2;
		naviosInimigos[j]->addMercadoria(merc);
		int peixe = navios[i]->getPeixe();
		naviosInimigos[j]->addPeixe(peixe);
		naviosInimigos[j]->addAgua(navios[i]->get_agua());
		navios[i]->destruir();
	}
	return true;
}

void Jogo::procuraBatalhas(){
	string s;
	for(int i=0;i<navios.size();i++){
		if(navios[i]->isAtivo()){
			if(navios[i]->get_soldados() != 0){
				for(int j=0;j<8;j++){
					int en = procuraInimigos(j, i);
					if (batalha(i, en)) {
						s += "Navio "; s += to_string(i); s += " batalhou "; s += " contra navioInimigo "; s += to_string(en);
						log.push_back(s);
					}
				}
			}
			else {
				for (int j = 0; j < 8; j++) {
					if (procuraInimigos(j, i) != -1)
					{
						s += "Navio "; s += to_string(i); s += " foi destruido";
						log.push_back(s);
						navios[i]->destruir();
					}
				}
			}
		}
	}
}
void Jogo::resetMoveu() {
	for (int i = 0; i < navios.size(); i++) {
		navios[i]->setMoveu(false);
	}
	for (int i = 0; i < naviosInimigos.size(); i++)
	{
		naviosInimigos[i]->setMoveu(false);
	}
}

void Jogo::spawnPeixes() {
	for(int i = 0;i<mapa.size();i++){
		if (mapa[i].getTipo() == '.' && mapa[i].getPeixe() < 1) {
			mapa[i].addPeixe();
		}
	}
}

void Jogo::spawnInimigos() {
	// 1 - f�cil // 2 - dificil
	coords pos;
	int x, y;
	string s;
	switch (dificuldade) {
	case 1:
		if (geraNumero(100) < 10) { // probabilidade de spawnar um pirata (20%)
			do {
				x = geraNumero(config.colunas);
				y = geraNumero(config.linhas);
				pos = semFronteiras(x, y);
			} while (!isAgua(pos.x, pos.y) || isOcupado(pos.x, pos.y));
			// decidir o seu tipo (50%)
			if (50 < geraNumero(100)) { // veleiro
				acrescentaNavioPirata(x, y, 'V');
			}
			else { // fragata
				acrescentaNavioPirata(x, y, 'F');
			}
			s += "Inimigo acrescentado";
			log.push_back(s);
		}
		break;
	case 2:
		if (geraNumero(100) < 33) {
			do {
				x = geraNumero(config.colunas);
				y = geraNumero(config.linhas);
				pos = semFronteiras(x, y);
			} while (!isAgua(pos.x, pos.y) || isOcupado(pos.x, pos.y));
			// decidir o seu tipo (50%)
			if (50 < geraNumero(100)) { // veleiro
				acrescentaNavioPirata(x, y, 'V');
			}
			else { // fragata
				acrescentaNavioPirata(x, y, 'F');
			}
			s += "Inimigo acrescentado";
			log.push_back(s);
		}
		break;
	default:
		cout << "Dificuldade exclusiva para premium." << endl;
		break;
	}
}
void Jogo::inimigoTransfereSoldados(int i, int e) {
	int max = naviosDeriva[i]->maxSoldados(naviosInimigos[e]->get_soldados() / 2);
	naviosInimigos[e]->set_soldados(naviosInimigos[e]->get_soldados() - max);
	naviosDeriva[i]->set_soldados(max);
}
void Jogo::amigoTransfereAgua(int ind1, int ind2) {
	int max = naviosDeriva[ind1]->addAgua(navios[ind2]->get_agua() / 2);
	navios[ind2]->set_agua(navios[ind2]->get_agua() - max);
}
void Jogo::amigoTransfereSoldados(int ind1, int ind2) {
	int max = naviosDeriva[ind1]->maxSoldados(navios[ind2]->get_soldados() / 2);
	navios[ind2]->set_soldados(navios[ind2]->get_soldados() - max);
	naviosDeriva[ind1]->set_soldados(max);
}
void Jogo::navioSemDono() {
	int e, a, max;
	string s;
	for (int i = 0 , e=-1, a=-1; i < naviosDeriva.size(); ) {
		for (int j = 0; j < 8 && e == -1 && a == -1; j++) {
			e = procuraInimigosDeriva(j, i);
			a = procuraAmigosDeriva(j, i);
		}
		if (e != -1) {
			if (naviosDeriva[i]->getTipo() == 'V' || naviosDeriva[i]->getTipo() == 'F') {// navio passa a ser pirata
				inimigoTransfereSoldados(i, e);
				Navio * p = naviosDeriva[i];
				naviosDeriva[i]->resetCliente();
				naviosInimigos.push_back(p);
				naviosDeriva.erase(naviosDeriva.begin() + i);
				s += "Barco a deriva "; s += to_string(i); s += " foi conquistado por piratas";
				log.push_back(s);
			}
			else {
				naviosDeriva[i]->setAtivo(false); // barco à deriva é destruido
				s += "Barco a deriva "; s += to_string(i); s += " foi destruido por piratas";
				log.push_back(s);
			}
		}else if (a != -1) { // navio passa a ser amigo
			amigoTransfereSoldados(i, a);
			amigoTransfereAgua(i, a);
			Navio * p = naviosDeriva[i];
			navios.push_back(p);
			naviosDeriva.erase(naviosDeriva.begin() + i);
			s += "Barco a deriva "; s += to_string(i); s += " foi conquistado pelo jogador";
			log.push_back(s);
		}
		else if (a == -1 && e == -1)
			i++;
	}
}
void Jogo::bebeAgua() {
	for (int i = 0; i < navios.size(); i++){
		if (navios[i]->get_agua() <= 0)
			navios[i]->set_soldados(navios[i]->get_soldados()- 1);
		else{
			navios[i]->set_agua(navios[i]->get_agua() - navios[i]->get_soldados());
			if(navios[i]->get_soldados()<=0)
			{
				Navio* p = navios[i];
				p->resetCliente();
				naviosDeriva.push_back(p);
				navios.erase(navios.begin() + i);
			}
		}
	}
}
void Jogo::processaPesca() {
	string s;
	if(evento != nullptr) {
		if (evento->getTipo() == 'C') {
			for (int i = 0; i < navios.size(); i++) {
				if (navios[i]->cargaLivre() > 0) {
					int x = navios[i]->get_x();
					int y = navios[i]->get_y();
					if (mapa[(config.colunas * y) + x].pesca()) {
						navios[i]->addPeixe(1);
						s += "O barco "; s += to_string(i); s += " pescou em {"; s += to_string(x); s += ","; s += to_string(y); s += "}.";
						log.push_back(s);
					}
				}
			}
		}
		else {
			for (int i = 0; i < navios.size(); i++) {
				if (navios[i]->getTipo() == 'E' && navios[i]->cargaLivre() > 0) {
					if (mapa[(config.colunas * navios[i]->get_y()) + navios[i]->get_x()].pesca()) {
						navios[i]->addPeixe(1);
						s += "O barco "; s += to_string(i); s += " pescou em {"; s += to_string(navios[i]->get_x()); s += ","; s += to_string(navios[i]->get_y()); s += "}.";
						log.push_back(s);
					}
				}
			}
		}
	}
	else {
		for (int i = 0; i < navios.size(); i++) {
			if (navios[i]->getTipo() == 'E' && navios[i]->cargaLivre() > 0) {
				if (mapa[(config.colunas * navios[i]->get_y()) + navios[i]->get_x()].pesca()) {
					navios[i]->addPeixe(1);
					s += "O barco "; s += to_string(i); s += " pescou em {"; s += to_string(navios[i]->get_x()); s += ","; s += to_string(navios[i]->get_y()); s += "}.";
					log.push_back(s);
				}
			}
		}
		
	}
	spawnPeixes();
	for (int i = 0; i < navios.size(); i++) {
		if (navios[i]->getTipo() == 'G' || !navios[i]->getTipo() == 'V') {
			for (int j = 0; j < 8; j++) {
				int ind = procuraAmigos(j, i);
				if (ind != -1) {
					if (navios[ind]->getTipo() == 'E')
					{
						if (navios[i]->cargaLivre() > 0) {
							if (navios[ind]->getPeixe() > 0) {
								trocaPeixe(i, ind);
							}
						}
					}
				}
			}
		}
	}
}

void Jogo::trocaAgua(int a, int s)
{
	if (navios[a]->aguaLivre() > 0) {
		int quant = navios[a]->addAgua(navios[s]->get_agua() - (navios[s]->get_soldados() + 1));
		navios[s]->tiraAgua(quant);
		navios[a]->set_agua(navios[a]->get_agua()+quant);
	}
}

void Jogo::trocaPeixe(int b, int e) {
	if (navios[b]->cargaLivre() < navios[e]->getPeixe()){
		int quant = navios[b]->cargaLivre();
		navios[e]->tiraPeixe(quant);
		navios[b]->addPeixe(quant);
	}
	else {
		int quant = navios[e]->getPeixe();
		navios[e]->setPeixe(0);
		navios[b]->addPeixe(quant);
	}
}

bool Jogo::moveDeriva(int t, int pos)
{
	coords c;
	switch(t){
	case 0:
		c = semFronteiras(naviosDeriva[pos]->get_x()-1, naviosDeriva[pos]->get_y()-1);
		break;
	case 1:
		c = semFronteiras(naviosDeriva[pos]->get_x(), naviosDeriva[pos]->get_y() - 1);
		break;
	case 2:
		c = semFronteiras(naviosDeriva[pos]->get_x() + 1, naviosDeriva[pos]->get_y() - 1);
		break;
	case 3:
		c = semFronteiras(naviosDeriva[pos]->get_x() - 1, naviosDeriva[pos]->get_y());
		break;
	case 4:
		c = semFronteiras(naviosDeriva[pos]->get_x() + 1, naviosDeriva[pos]->get_y());
		break;
	case 5:
		c = semFronteiras(naviosDeriva[pos]->get_x() - 1, naviosDeriva[pos]->get_y() + 1);
		break;
	case 6:
		c = semFronteiras(naviosDeriva[pos]->get_x(), naviosDeriva[pos]->get_y() + 1);
		break;
	case 7:
		c = semFronteiras(naviosDeriva[pos]->get_x() + 1, naviosDeriva[pos]->get_y() + 1);
		break;
	}
	if (isAgua(c.x, c.y) && !isOcupado(c.x,c.y)){
		naviosDeriva[pos]->set_x(c.x);
		naviosDeriva[pos]->set_y(c.y);
		return true;
	}
	return false;
}
Jogo & Jogo::operator=(const Jogo & ob) {
	if (this == &ob)
		return *this;

	delete jogador;
	
	for (int i = 0; i < navios.size(); i++)
		delete navios[i];
	navios.clear();

	for (int i = 0; i < naviosInimigos.size(); i++)
		delete naviosInimigos[i];
	naviosInimigos.clear();

	for (int i = 0; i < naviosDeriva.size(); i++)
		delete naviosDeriva[i];
	naviosDeriva.clear();

	for (int i = 0; i < portos.size(); i++)
		delete portos[i];
	portos.clear();

	for (int i = 0; i < portosInimigos.size(); i++)
		delete portosInimigos[i];

	portosInimigos.clear();

	delete evento;

	for (int i = 0; i < ob.navios.size(); i++)
	{
		auto p = ob.navios[i]->duplica();
		navios.push_back(p);
	}

	for (int i = 0; i < ob.naviosInimigos.size(); i++)
	{
		auto p = ob.naviosInimigos[i]->duplica();
		naviosInimigos.push_back(p);
	}

	for (int i = 0; i < ob.naviosDeriva.size(); i++)
	{
		auto p = ob.naviosDeriva[i]->duplica();
		naviosDeriva.push_back(p);
	}

	for (int i = 0; i < ob.portos.size(); i++)
	{
		auto p = ob.portos[i]->duplica();
		portos.push_back(p);
	}

	for (int i = 0; ob.portosInimigos.size(); i++)
	{
		auto p = ob.portos[i]->duplica();
		portosInimigos.push_back(p);
	}

	dificuldade = ob.dificuldade;
	
	for (int i = 0; i < mapa.size(); i++)
	{
		mapa[i].set_x(ob.mapa[i].get_x());
		mapa[i].set_y(ob.mapa[i].get_y());
		mapa[i].setPeixe(ob.mapa[i].getPeixe());
		mapa[i].setPorto(ob.mapa[i].getPorto());
	}

	config = ob.config;
	evento = ob.evento;

	return *this;
}
void Jogo::reporAgua() {
	for (int i = 0; i < navios.size(); i++) {
		if (isPortoAmigo(navios[i]->get_x(), navios[i]->get_y()))
			navios[i]->set_agua(navios[i]->maxAgua());
		else
		{
			if(navios[i]->getTipo()!='S'){
				for (int j = 0; j < 8; j++) {
					int ind = procuraAmigos(j, i);
					if (ind != -1) {
						if (navios[ind]->getTipo() == 'S')
						{
							if (navios[ind]->get_agua() > navios[ind]->get_soldados() + 1) {
								trocaAgua(i, ind);
							}
						}
					}
				}
			}
			else
				navios[i]->set_agua(navios[i]->addAgua(100));
		}
		
	}
}

void Jogo::procuraBatalhasPorto() {
	string s;
	for (int i = 0; i < navios.size(); i++) {
		if (navios[i]->isAtivo()) {
			if (navios[i]->get_soldados() != 0) {
				for (int j = 0; j < 8; j++) {
					int en = procuraPortoInimigo(j, i); 
					if (batalhaPorto(i, en)) {
						navios[i]->set_soldados(ceil(navios[i]->get_soldados() * 0.9));
						s += "Navio "; s += to_string(i); s += " batalhou contra porto "; s += to_string(en);
						log.push_back(s);
					}
				}
			}
		}
	}
	for (int i = 0; i < naviosInimigos.size(); i++) {
		if (naviosInimigos[i]->isAtivo()) {
			if (naviosInimigos[i]->isAtivo()) {
				for (int j = 0; j < 8; j++) {
					int en = procuraPortoAmigo(j, i);
					if (batalhaPortoPirata(i, en)) {
						naviosInimigos[i]->set_soldados(ceil(naviosInimigos[i]->get_soldados() * 0.9));
						s += "Navio Pirata "; s += to_string(i); s += " batalhou contra porto "; s += to_string(en);
						log.push_back(s);
					}
				}
			}
		}
	}
}

int Jogo::procuraPortoInimigo(int t, int i){
	coords c;
	int mapa_pos;
		switch (t)
		{
		case 0:
			c = semFronteiras(navios[i]->get_x() - 1, navios[i]->get_y() - 1);
			break;
		case 1:
			c = semFronteiras(navios[i]->get_x(), navios[i]->get_y() - 1);
			break;
		case 2:
			c = semFronteiras(navios[i]->get_x() + 1, navios[i]->get_y() - 1);
			break;
		case 3:
			c = semFronteiras(navios[i]->get_x() - 1, navios[i]->get_y());
			break;
		case 4:
			c = semFronteiras(navios[i]->get_x() + 1, navios[i]->get_y());
			break;
		case 5:
			c = semFronteiras(navios[i]->get_x() - 1, navios[i]->get_y() + 1);
			break;
		case 6:
			c = semFronteiras(navios[i]->get_x(), navios[i]->get_y() + 1);
			break;
		case 7:
			c = semFronteiras(navios[i]->get_x() + 1, navios[i]->get_y() + 1);
			break;
		}
	mapa_pos = c.y * config.colunas + c.x;
	if(mapa[mapa_pos].getPorto() != nullptr)
		if (islower(mapa[mapa_pos].getPorto()->getID()))
			return mapa_pos;
	
	return -1;
}

int Jogo::procuraPortoAmigo(int t, int i) {
	coords c;
	int mapa_pos;
	switch (t)
	{
	case 0:
		c = semFronteiras(naviosInimigos[i]->get_x() - 1, naviosInimigos[i]->get_y() - 1);
		break;
	case 1:
		c = semFronteiras(naviosInimigos[i]->get_x(), naviosInimigos[i]->get_y() - 1);
		break;
	case 2:
		c = semFronteiras(naviosInimigos[i]->get_x() + 1, naviosInimigos[i]->get_y() - 1);
		break;
	case 3:
		c = semFronteiras(naviosInimigos[i]->get_x() - 1, naviosInimigos[i]->get_y());
		break;
	case 4:
		c = semFronteiras(naviosInimigos[i]->get_x() + 1, naviosInimigos[i]->get_y());
		break;
	case 5:
		c = semFronteiras(naviosInimigos[i]->get_x() - 1, naviosInimigos[i]->get_y() + 1);
		break;
	case 6:
		c = semFronteiras(naviosInimigos[i]->get_x(), naviosInimigos[i]->get_y() + 1);
		break;
	case 7:
		c = semFronteiras(naviosInimigos[i]->get_x() + 1, naviosInimigos[i]->get_y() + 1);
		break;
	}
	mapa_pos = c.y * config.colunas + c.x;
	if (mapa[mapa_pos].getPorto() != nullptr)
		if (isupper(mapa[mapa_pos].getPorto()->getID()))
			return mapa_pos;

		return -1;
}

bool Jogo::batalhaPorto(int i, int m) {
	if (m == -1)
		return false;
	int poder_porto = geraNumero(101);
	if (poder_porto <= navios[i]->get_soldados())
		trocaPorto(m);
	return true;
}

bool Jogo::batalhaPortoPirata(int i, int m){
	if (m == -1)
		return false;
	int poder_porto = geraNumero(101);
	if (poder_porto <= naviosInimigos[i]->get_soldados())
		trocaPorto(m);
	return true;
}

void Jogo::trocaPorto(int m) {
	string s;
	char a;
	Porto* p = mapa[m].getPorto();
	if (islower(p->getID())) {
		for (int i = 0; i < portosInimigos.size(); i++){
			if (portosInimigos[i] == p) {
				portosInimigos.erase(portosInimigos.begin() + i);
				p->setID(toupper(p->getID()));
				portos.push_back(p);
				s += "O jogador conquistou o porto "; s += p->getID();
				log.push_back(s);
			}
		}
	}
	else {
		for (int i = 0; i < portos.size(); i++) {
			if (portos[i] == p) {
				portos.erase(portos.begin() + i);
				p->setID(tolower(p->getID()));
				portosInimigos.push_back(p);
				s += "Os piratas conquistaram o porto "; s += p->getID();
				log.push_back(s);
			}
		}
	}
}
void Jogo::criaEventoCoords(char tipo, int x, int y) {
	switch (tipo) {
	case 'T':
		evento = new Tempestade(x, y);
		break;
	case 'C':
		evento = new Calmaria(x, y);
		break;
	}
}
void Jogo::criaEventoNav(char tipo, int id){
	if (pesquisaNavio(id) == -1)
		return;
	switch (tipo) {
	case 'S':
		evento = new Sereias(id);
		break;
	case 'M':
		evento = new Motim(id);
		break;
	}
}
void Jogo::processaEventos()
{
	string s;
	if(evento==nullptr){
		if(geraNumero(100) < config.probevento)
		{
			if(geraNumero(100)<config.probtempestade)
			{
				coords c = gera2x2();
				evento = new Tempestade(c.x, c.y);
				s += "Tempestade ocorreu entre as coordenadas {"; s += to_string(c.x); s += ","; s += to_string(c.y); s += "}";
				log.push_back(s);
			}
			else if(geraNumero(100-config.probtempestade)<config.probsereias){
				if (navios.size() == 0)
					return;
				int pos = geraNumero(navios.size());
				evento = new Sereias(pos);
				s += "Sereias afetaram o navio "; s += to_string(pos);
				log.push_back(s);
			}
			else if(geraNumero(100-(config.probtempestade + config.probsereias))<config.probcalmaria)
			{
				coords c = gera2x2();
				evento = new Calmaria(c.x, c.y);
				s += "Calmaria ocorreu entre as coordenadas {"; s += to_string(c.x); s += ","; s += to_string(c.y); s += "}";
				log.push_back(s);
			}
			else if(geraNumero(100 - (config.probtempestade + config.probsereias + config.probcalmaria)) < config.probmotim)
			{
				if (navios.size() == 0)
					return;
				int id = navios[geraNumero(navios.size())]->get_id();
				evento = new Motim(id);
				s += "O navio "; s += to_string(id); s += " entrou em motim";
				log.push_back(s);
			}
		}
	}
	if(evento != nullptr){
		evento->atuaEvento(this);	
		evento->baixaDur();
		checkEvento();
	}
}

void Jogo::checkEvento()
{
	if(evento->getDur() == 0)
	{
		if(evento->getTipo()=='M')
		{
			int i;
			Navio* n = evento->getNavio();
			for (i = 0; i < naviosInimigos.size() && naviosInimigos[i] != n; i++);
			if(i != naviosInimigos.size()){
				naviosInimigos.erase(naviosInimigos.begin() + i);
				navios.push_back(n);
			}
		}
		else if(evento->getTipo()=='C')
		{
			for(int i=0;i<navios.size();i++){
				if(afetado(i))
				{
					adicionaMoedas(100);
				}
			}

		}
		delete evento;
		evento = nullptr;
	}
}

Jogo::~Jogo() {
	for (Navio * p : navios)
		delete p;
	for (Navio * p : naviosInimigos)
		delete p;	
	for (Navio * p : naviosDeriva)
		delete p;
	for (Porto *p : portos)
		delete p;
	for (Porto*p : portosInimigos)
		delete p;
	delete jogador;
}

char Jogo::mapa_getTipo(int i)
{
	return mapa[i].getTipo();
}

void Jogo::evento_tempestade(int x, int y)
{
	string s;
	coords cse;
	cse.x = x; cse.y = y;
	for(int i=0;i<navios.size();i++)
	{
		if((navios[i]->get_x()==cse.x && navios[i]->get_y() == cse.y) || (navios[i]->get_x() == cse.x+1 && navios[i]->get_y() == cse.y) || (navios[i]->get_x() == cse.x && navios[i]->get_y() == cse.y+1) || (navios[i]->get_x() == cse.x + 1 && navios[i]->get_y() == cse.y + 1))
		{
			navios[i]->reageTempestade();
			s += "Navio "; s += to_string(navios[i]->get_id()); s += " foi apanhado numa tempestade";
			log.push_back(s);
		}
	}
	for (int i = 0; i < naviosInimigos.size(); i++)
	{
		if ((naviosInimigos[i]->get_x() == cse.x && naviosInimigos[i]->get_y() == cse.y) || (naviosInimigos[i]->get_x() == cse.x + 1 && naviosInimigos[i]->get_y() == cse.y) || (naviosInimigos[i]->get_x() == cse.x && naviosInimigos[i]->get_y() == cse.y + 1) || (naviosInimigos[i]->get_x() == cse.x + 1 && naviosInimigos[i]->get_y() == cse.y + 1))
		{
			naviosInimigos[i]->reageTempestade();
			s += "NavioInimigo "; s += to_string(naviosInimigos[i]->get_id()); s += " foi apanhado numa tempestade";
			log.push_back(s);
		}
	}
}

void Jogo::evento_sereias(int id) {
	int qual = pesquisaNavio(id);
	if (qual == -1)
		return;
	int atual = navios[qual]->get_soldados();
	navios[qual]->set_soldados(atual - 0.1 * atual);
}
coords Jogo::gera2x2() {
	coords pos1, pos2, pos3, pos4;
	bool valid = false;
	while(!valid){
		int x = geraNumero(config.colunas);
		int y = geraNumero(config.linhas);
		pos1 = semFronteiras(x, y);
		if (isAgua(pos1.x, pos1.y)) {
			pos2 = semFronteiras(x + 1, y);
			if (isAgua(pos2.x, pos2.y)) {
				pos3 = semFronteiras(x, y + 1);
				if (isAgua(pos3.x, pos3.y)) {
					pos4 = semFronteiras(x + 1, y + 1);
					if (isAgua(pos4.x, pos4.y))
					{
						valid = true;
					}
				}
			}
		}
	}
	return pos1;
}
coords Jogo::geraCoordsDestino(int id) {
	coords erro, d;
	erro.x = -1;
	erro.y = -1;
	int pos = geraNumero(8);
	switch (pos) {
	case 0:
		d = semFronteiras(navios[id]->get_x() - 1, navios[id]->get_y() - 1);
		if(isAgua(d.x,d.y) && !isOcupado(d.x,d.y))
			return d;
		return erro;
		break;
	case 1:
		d = semFronteiras(navios[id]->get_x(), navios[id]->get_y() - 1);
		if (isAgua(d.x, d.y) && !isOcupado(d.x, d.y))
			return d;
		return erro;
		break;
	case 2:
		d = semFronteiras(navios[id]->get_x() + 1, navios[id]->get_y() - 1);
		if (isAgua(d.x, d.y) && !isOcupado(d.x, d.y))
			return d;
		return erro;
	break;
	case 3:
		d = semFronteiras(navios[id]->get_x() - 1, navios[id]->get_y());
		if (isAgua(d.x, d.y) && !isOcupado(d.x, d.y))
			return d;
		return erro;
		break;
	case 4:
		d = semFronteiras(navios[id]->get_x() + 1, navios[id]->get_y());
		if (isAgua(d.x, d.y) && !isOcupado(d.x, d.y))
			return d;
		return erro;
		break;
	case 5:
		d = semFronteiras(navios[id]->get_x() - 1, navios[id]->get_y() + 1);
		if (isAgua(d.x, d.y) && !isOcupado(d.x, d.y))
			return d;
		return erro;
		break;
	case 6:
		d = semFronteiras(navios[id]->get_x(), navios[id]->get_y() + 1);
		if (isAgua(d.x, d.y) && !isOcupado(d.x, d.y))
			return d;
		return erro;
		break;
	case 7:
		d = semFronteiras(navios[id]->get_x() + 1, navios[id]->get_y() + 1);
		if (isAgua(d.x, d.y) && !isOcupado(d.x, d.y))
			return d;
		return erro;
		break;
	}
	return erro;
}

coords Jogo::geraCoordsDestinoPirata(int id) {
	coords erro, d;
	erro.x = -1;
	erro.y = -1;
	int pos = geraNumero(8);
	switch (pos) {
	case 0:
		d = semFronteiras(naviosInimigos[id]->get_x() - 1, naviosInimigos[id]->get_y() - 1);
		if (isAgua(d.x, d.y) && !isOcupado(d.x, d.y))
			return d;
		return erro;
		break;
	case 1:
		d = semFronteiras(naviosInimigos[id]->get_x(), naviosInimigos[id]->get_y() - 1);
		if (isAgua(d.x, d.y) && !isOcupado(d.x, d.y))
			return d;
		return erro;
		break;
	case 2:
		d = semFronteiras(naviosInimigos[id]->get_x() + 1, naviosInimigos[id]->get_y() - 1);
		if (isAgua(d.x, d.y) && !isOcupado(d.x, d.y))
			return d;
		return erro;
		break;
	case 3:
		d = semFronteiras(naviosInimigos[id]->get_x() - 1, naviosInimigos[id]->get_y());
		if (isAgua(d.x, d.y) && !isOcupado(d.x, d.y))
			return d;
		return erro;
		break;
	case 4:
		d = semFronteiras(naviosInimigos[id]->get_x() + 1, naviosInimigos[id]->get_y());
		if (isAgua(d.x, d.y) && !isOcupado(d.x, d.y))
			return d;
		return erro;
		break;
	case 5:
		d = semFronteiras(naviosInimigos[id]->get_x() - 1, naviosInimigos[id]->get_y() + 1);
		if (isAgua(d.x, d.y) && !isOcupado(d.x, d.y))
			return d;
		return erro;
		break;
	case 6:
		d = semFronteiras(naviosInimigos[id]->get_x(), naviosInimigos[id]->get_y() + 1);
		if (isAgua(d.x, d.y) && !isOcupado(d.x, d.y))
			return d;
		return erro;
		break;
	case 7:
		d = semFronteiras(naviosInimigos[id]->get_x() + 1, naviosInimigos[id]->get_y() + 1);
		if (isAgua(d.x, d.y) && !isOcupado(d.x, d.y))
			return d;
		return erro;
		break;
	}
	return erro;
}

void Jogo::evento_calmaria(int x, int y) {
	string s;
	coords csd, cid, cie, atual, cse;
	cse.x = x; cse.y = y;
	csd = semFronteiras(cse.x + 1, cse.y);
	cid = semFronteiras(cse.x + 1, cse.y + 1);
	cie = semFronteiras(cse.x, cse.y + 1);

	for (int i = 0; i < navios.size(); i++)
	{
		atual.x = navios[i]->get_x();
		atual.y = navios[i]->get_y();
		if (atual == cse || atual == csd || atual == cid || atual == cie) {
			navios[i]->setMoveu(true);
		}
	}
	for (int i = 0; i < naviosInimigos.size(); i++)
	{
		atual.x = naviosInimigos[i]->get_x();
		atual.y = naviosInimigos[i]->get_y();
		if (atual == cse || atual == csd || atual == cie || atual == cid){
			naviosInimigos[i]->setMoveu(true);
		}
	}
	s += "Calmaria afeto coordenadas entre {"; s += to_string(cse.x); s += ";"; s += to_string(cse.y); s += "} e {"; s += to_string(cid.x); s += ";"; s += to_string(cid.y); s += "}";
	log.push_back(s);
}

Navio* Jogo::evento_motim(bool & first, int a)
{
	string s;
	int nav = pesquisaNavio(a);
	if(evento->getDur()==5){
		if (navios[nav]->getTipo() == 'V' || navios[nav]->getTipo() == 'F') {
			Navio* n = navios[nav];
			navios.erase(navios.begin() + nav);
			naviosInimigos.push_back(n);
			s += "Motim afetou o navio "; s += to_string(nav);
			log.push_back(s);
			return n;
		}
		navios[nav]->destruir();
		s += "Motim destruiu o navio "; s += to_string(nav);
		log.push_back(s);
		return nullptr;
	}
	first = false;
	return nullptr;
}

void Jogo::eliminaDestrocos() {
	for (auto it = navios.begin(); it != navios.end(); )
		if (!((*it)->isAtivo())) {
			delete *it;
			it = navios.erase(it);
		}
		else
			++it;
	for (auto it = naviosInimigos.begin(); it != naviosInimigos.end(); )
		if (!((*it)->isAtivo())) {
			delete *it;
			it = naviosInimigos.erase(it);
		}
		else
			++it;
	for (auto it = naviosDeriva.begin(); it != naviosDeriva.end(); )
		if (!((*it)->isAtivo())) {
			delete *it;
			it = naviosDeriva.erase(it);
		}
		else
			++it;
}

bool Jogo::afetado(int i)
{
	if (navios[i]->get_x() == evento->get_x() && navios[i]->get_y() == evento->get_y())
		return true;
	if (navios[i]->get_x() == evento->get_x() && navios[i]->get_y() == evento->get_y() + 1)
		return true;
	if (navios[i]->get_x() == evento->get_x() + 1 && navios[i]->get_y() == evento->get_y())
		return true;
	if (navios[i]->get_x() == evento->get_x() + 1 && navios[i]->get_y() == evento->get_y() + 1)
		return true;
	return false;
}

vector<string> Jogo::devolveLog() {
	return log;
}
void Jogo::trataLog() {
	for (int i = 0; i < log.size(); i++)
		log.erase(log.begin() + i);
}
void Jogo::updateLog(string s) {
	log.push_back(s);
}
void Jogo::movimentoAuto(vector <string> & ordens) {
	for (int i = 0; i < navios.size(); i++) {
		if (!navios[i]->getMoveu()) {
			navios[i]->fazAuto(this, navios[i]->get_id(), ordens);
		}
	}
	for (int i = 0; i < naviosInimigos.size(); i++) {
		if (!naviosInimigos[i]->getMoveu()) {
			naviosInimigos[i]->fazAuto(this, naviosInimigos[i]->get_id(), ordens);
		}
	}
	for (int i = 0; i < naviosDeriva.size(); i++)
	{
		if(geraNumero(100)<50)
		{
			moveDeriva(geraNumero(8), i);
		}
	}
}

void Jogo::escunaAutoFull(int i, vector <string> & ordens) {
	int p = geraNumero(portos.size());
	if(!vaiparaporto(navios[i]->get_id(), portos[p]->getID())){
		string a;
		a += "vaiparaporto ";
		a += portos[p]->getID();
		ordens.push_back(a);
	}
}

void Jogo::escunaAuto(int i, vector <string> &ordens) {
	int pos=-1;
	int pos_atual = navios[i]->get_y()*config.colunas + navios[i]->get_x();
	for(int j=0;j<2 && mapa[pos_atual].getPeixe() != 1 ;j++){
		for (int t = 0; t < 8 && pos != -1; t++) {
			pos=procuraPeixe(t, i);
		}
		if (pos != -1){
			if (!vaiparacoords(navios[i]->get_id(), mapa[pos].get_x(), mapa[pos].get_y())) {
				string a;
				a += "vaiparacoords ";
				a += mapa[pos].get_x();
				a += " ";
				a += mapa[pos].get_y();
				ordens.push_back(a);
			}
		}
	}
}

int Jogo::procuraPeixe(int t, int i) {
	coords c;
	int mapa_pos;
	switch (t)
	{
	case 0:
		c = semFronteiras(navios[i]->get_x() - 1, navios[i]->get_y() - 1);
		break;
	case 1:
		c = semFronteiras(navios[i]->get_x(), navios[i]->get_y() - 1);
		break;
	case 2:
		c = semFronteiras(navios[i]->get_x() + 1, navios[i]->get_y() - 1);
		break;
	case 3:
		c = semFronteiras(navios[i]->get_x() - 1, navios[i]->get_y());
		break;
	case 4:
		c = semFronteiras(navios[i]->get_x() + 1, navios[i]->get_y());
		break;
	case 5:
		c = semFronteiras(navios[i]->get_x() - 1, navios[i]->get_y() + 1);
		break;
	case 6:
		c = semFronteiras(navios[i]->get_x(), navios[i]->get_y() + 1);
		break;
	case 7:
		c = semFronteiras(navios[i]->get_x() + 1, navios[i]->get_y() + 1);
		break;
	}
	mapa_pos = c.y * config.colunas + c.x;
	if (mapa[mapa_pos].getPeixe()==1)
	{
		return mapa_pos;
	}
	else
		return -1;
}

void Jogo::saveGame(string nome) {
	string str;

	ofstream save;
	str += "logs/"; str += nome;
	save.open(str);
	
	save << "linhas " << config.linhas << endl;
	save << "colunas " << config.colunas << endl;
	for (int i = 0; i < config.linhas; i++) {
		for (int j = 0; j < config.colunas; j++)
			if (mapa[i*config.colunas + j].isPorto())
				save << mapa[i*config.colunas + j].getPorto()->getID();
			else
				save << mapa[i * config.colunas + j].getTipo();
		save << endl;
	}
	save << "moedas " << config.moedas << endl;
	save << "probpirata " << config.probpirata<< endl;
	save << "preconavio " << config.preconavio<< endl;
	save << "precoveleiro " << config.precoveleiro<< endl;
	save << "precoescuna " << config.precoescuna<< endl;
	save << "precogaleao " << config.precogaleao<< endl;
	save << "precofragata " << config.precofragata<< endl;
	save << "precoespecial " << config.precoespecial<< endl;
	save << "precosoldado " << config.precosoldado<< endl;
	save << "precopeixe " << config.precovendpeixe<< endl;
	save << "precocompmercad " << config.precocompmercad<< endl;
	save << "precovendmercad " << config.precovendmercad<< endl;
	save << "soldadosporto " << config.soldadosporto<< endl;
	save << "probevento " << config.probevento<< endl;
	save << "probtempestade " << config.probtempestade<< endl;
	save << "probsereias " << config.probsereias<< endl;
	save << "probcalmaria " << config.probcalmaria<< endl;
	save << "probmotim " << config.probmotim<< endl;
	save << "dificuldade " << getDificuldade() << endl;
	save << "jogador " << getPlayer() << " " << jog_getmoedas() << " " << pontuacao() << endl;
	
	save << navios.size() << endl;
	
	for (int i = 0; i < navios.size(); i++) {
		if (navios[i]->getTipo() != 'S' && navios[i]->getTipo() != 'F')
			save << navios[i]->getTipo() << " " << navios[i]->get_id() << " " << navios[i]->get_agua()
			<< " " << navios[i]->get_soldados() << " " << navios[i]->get_x() << " " << navios[i]->get_y() <<
			" " << navios[i]->isAtivo() << " " << navios[i]->getMoveu() << " " <<
			navios[i]->getMercadoria() << " " << navios[i]->getPeixe() << endl;
		else
			save << navios[i]->getTipo() << " " << navios[i]->get_id() << " " << navios[i]->get_agua()
			<< " " << navios[i]->get_soldados() << " " << navios[i]->get_x() << " " << navios[i]->get_y() <<
			" " << navios[i]->isAtivo() << " " << navios[i]->getMoveu() << endl;
	}
	
	save << naviosInimigos.size() << endl;
	
	for(int i = 0 ; i < naviosInimigos.size(); i++)
		save << naviosInimigos[i]->getTipo() << " " << naviosInimigos[i]->get_id() << " " << naviosInimigos[i]->get_soldados() <<
		" " << naviosInimigos[i]->get_x() << " " << naviosInimigos[i]->get_y() <<
		" " << naviosInimigos[i]->isAtivo() << " " << naviosInimigos[i]->getMoveu() << endl;
	
	save << naviosDeriva.size() << endl;
	
	for(int i = 0 ; i < naviosDeriva.size(); i++)
		save << naviosDeriva[i]->getTipo() << " " << naviosDeriva[i]->get_id() << " " << naviosDeriva[i]->get_x() << " "
		<< naviosDeriva[i]->get_y() << " " << naviosDeriva[i]->isAtivo() << " " << naviosDeriva[i]->getMoveu() << endl;
	
	save.close();
}

void Jogo::limpaDados() {
	for (int i = 0; i < navios.size(); i++)
		delete navios[i];
	navios.clear();
	for (int i = 0; i < naviosInimigos.size(); i++)
		delete naviosInimigos[i];
	naviosInimigos.clear();
	for (int i = 0; i < naviosDeriva.size(); i++)
		delete naviosDeriva[i];
	naviosDeriva.clear();
	for (int i = 0; i < portos.size(); i++)
		delete portos[i];
	portos.clear();
	for (int i = 0; i < portosInimigos.size(); i++)
		delete portosInimigos[i];
	portosInimigos.clear();
	mapa.clear();
}

bool Jogo::loadGame(string nome) {
	char ch;
	string str, file;
	Config cfg;
	int aux, a, b, c, d, g, h, size;
	bool  e, f;
	file += "logs/"; file += nome;

	ifstream load(file);

	if (!load.is_open()) {
		return false;
	}
	limpaDados();
	for (auto i = 0; i < 2; i++)
	{
		getline(load, str);
		istringstream iss(str);
		iss >> str;
		if (str == "linhas")
			iss >> cfg.linhas;
		else
			iss >> cfg.colunas;
	}
	for (auto i = 0; i < cfg.linhas; i++)
	{
		for (auto j = 0; j < cfg.colunas; j++)
		{
			load >> ch;
			if (ch != '.' && ch != '+')
			{
				if (islower(ch)) {
					Porto * pt = new Porto(ch, j, i);
					portosInimigos.push_back(pt);
					Celula a(j, i, 'p', pt);
					mapa.push_back(a);
				}
				else {
					Porto * pt = new Porto(ch, j, i);
					portos.push_back(pt);
					Celula a(j, i, 'p', pt);
					mapa.push_back(a);
				}
			}
			else
			{
				Celula a(j, i, ch);
				mapa.push_back(a);
			}
		}
	}
	bool vars = true;
	while (vars)
	{
		getline(load, str);
		istringstream le(str);
		if (le >> str)
		{
			if (str == "probmotim")
				vars = false;
			var(str, le, cfg);
		}
	}

	if(getline(load, str)){
		istringstream le(str);
		le >> str;
		le >> aux;
		dificuldade = aux;
	}

	if (getline(load, str)) {
		istringstream le(str);
		le >> str;
		le >> str;
		jogador->setNome(str);
		le >> str;
		le >> aux;
		jogador->setMoedas(aux);
		le >> str;
		le >> aux;
		jogador->setPontuacao(aux);
	}

	if (getline(load, str))
	{
		istringstream le(str);
		le >> size;
	}
	else
		size = 0;
	for (int i = 0; i < size; i++)
	{
		getline(load, str);
		istringstream le(str);
		le >> ch;
		if (ch != 'S' || ch != 'F') {
			le >> aux;
			le >> a;
			le >> b;
			le >> c;
			le >> d;
			le >> e;
			le >> f;
			le >> g;
			le >> h;
			if (ch == 'V'){
				navios.push_back(new Veleiro(aux, a, b, c, d, e, f, g, h, cfg.precoveleiro));
			}
			if (ch == 'G')
				navios.push_back(new Galeao(aux, a, b, c, d, e, f, g, h, cfg.precogaleao));
			if (ch == 'E')
				navios.push_back(new Escuna(aux, a, b, c, d, e, f, g, h, cfg.precoescuna));
		}
		else
		{
			le >> aux;
			le >> a;
			le >> b;
			le >> c;
			le >> d;
			le >> e;
			le >> f;
			if (ch == 'S')
				navios.push_back(new Especial(aux, a, b, c, d, e, f, cfg.precoespecial));
			if (ch == 'F')
				navios.push_back(new Fragata(aux, a, b, c, d, e, f, cfg.precofragata));
		}


	}
	if (getline(load, str)) {
		istringstream le(str);
		le >> size;
	}
	else
		size = 0;

	for (int i = 0; i < size; i++)
	{
		getline(load, str);
		istringstream le(str);
		le >> ch;
		if (ch != 'S' || ch != 'F') {
			le >> aux;
			le >> a;
			le >> b;
			le >> c;
			le >> d;
			le >> e;
			le >> f;
			le >> g;
			le >> h;
			if (ch == 'V')
				naviosInimigos.push_back(new Veleiro(aux, a, b, c, d, e, f, g, h, cfg.precoveleiro));
			if (ch == 'G')
				naviosInimigos.push_back(new Galeao(aux, a, b, c, d, e, f, g, h, cfg.precogaleao));
			if (ch == 'E')
				naviosInimigos.push_back(new Escuna(aux, a, b, c, d, e, f, g, h, cfg.precoescuna));
		}
		else
		{
			le >> aux;
			le >> a;
			le >> b;
			le >> c;
			le >> d;
			le >> e;
			le >> f;
			if (ch == 'S')
				naviosInimigos.push_back(new Especial(aux, a, b, c, d, e, f, cfg.precoespecial));
			if (ch == 'F')
				naviosInimigos.push_back(new Fragata(aux, a, b, c, d, e, f, cfg.precofragata));
		}


	}
	
	if (getline(load, str)) {
		istringstream le(str);
		le >> size;
	}
	else
		size = 0;

	for (int i = 0; i < size; i++)
	{
		getline(load, str);
		istringstream le(str);
		le >> ch;
		if (ch != 'S' || ch != 'F') {
			le >> aux;
			le >> a;
			le >> b;
			le >> c;
			le >> d;
			le >> e;
			le >> f;
			le >> g;
			le >> h;
			if (ch == 'V')
				naviosDeriva.push_back(new Veleiro(aux, a, b, c, d, e, f, g, h, cfg.precoveleiro));
			if (ch == 'G')
				naviosDeriva.push_back(new Galeao(aux, a, b, c, d, e, f, g, h, cfg.precogaleao));
			if (ch == 'E')
				naviosDeriva.push_back(new Escuna(aux, a, b, c, d, e, f, g, h, cfg.precoescuna));
		}
		else
		{
			le >> aux;
			le >> a;
			le >> b;
			le >> c;
			le >> d;
			le >> e;
			le >> f;
			if (ch == 'S')
				naviosDeriva.push_back(new Especial(aux, a, b, c, d, e, f, cfg.precoespecial));
			if (ch == 'F')
				naviosDeriva.push_back(new Fragata(aux, a, b, c, d, e, f, cfg.precofragata));
		}
	}
	load.close();
	return true;
}

bool Jogo::delGame(const char *nome) {
	string str;
	int i;
	char file[20];
	str += "logs/"; str += nome;
	for (i = 0; i < str.length(); i++)
		file[i] = str.at(i);
	file[i] = '\0';
	cout << "lfag: " << file << endl;
	system("pause");
	ifstream logs(file);
	if (logs.is_open()) {
		logs.close();
		remove(file);
		return true;
	}
	return false;
}