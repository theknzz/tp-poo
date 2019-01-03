#ifndef INTERACAO_H
#define INTERACAO_H

#include <string>
#include <vector>

using namespace std;

#include "Jogo.h"

class Interacao
{
	Jogo * jogo;
public:
	Interacao(Jogo * jg);
	unsigned int lerUInt(string msg);
	unsigned int escolheOpcao(istringstream & iss);
	void menu();
	string lerNome(string pergunta);
	string perguntaOpcao();
	void opcaoMoverNavio(istringstream &iss);
	bool opcaoConfig(string);
	void opcaoCompraNavio(istringstream &iss);
	void opcaoCompraMercadoria(istringstream &iss);
	void opcaoVendeNavio(istringstream &iss);
	void opcaoVendeMercadoria(istringstream &iss);
	void opcaoDarMoedas(istringstream &iss);
	void opcaoCompraSoldados(istringstream &iss);
	void opcaoScript(istringstream &iss, vector <string> & ordens);
	void opcaoLista(istringstream &iss);
	void opcaoProx(vector <string> &ordens);
	void opcaoProx();
	void opcaoAcrescentaInimigo(istringstream & iss);
	void opcaoCriaEventoNavio(int opt, string cmd, istringstream & iss, vector <string> &ordens);
	void opcaoCriaEventoCoords(int opt, string cmd, istringstream & iss, vector <string> &ordens);
	void opcaoAutoGestao(istringstream & iss, int controlo);
	void opcaoStop(istringstream & iss, int controlo);
	void opcaoMostraPontuacao();
	bool opcaoSegueCoords(istringstream & iss);
	bool opcaoSeguePorto(istringstream & iss);
	bool executaOrdens(int opt, istringstream & iss, vector <string> & ordens);
	void processaOrdens(vector <string> & ordens);
	bool stringDigit(string s);
	void impVetor(vector <string> ordens);
	bool inicia();
	bool validaParametros(int opt, string cmd, istringstream & iss, vector <string> & ordens);
	void impLog(vector <string> log);
	void opcaoSave(istringstream & iss);
	void opcaoLoad(istringstream & iss);
	void opcaoDelete(istringstream & iss);
	virtual ~Interacao();
};

#endif