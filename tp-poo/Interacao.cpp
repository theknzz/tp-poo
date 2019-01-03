#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <cctype>

using namespace std;

#include "Interacao.h"
#include "Jogo.h"

Interacao::Interacao(Jogo * jg) {
	jogo = jg;
}

bool Interacao::inicia() {
	string fich;
	cout << "Insira o nome do ficheiro de configuracao: ";
	getline(cin, fich);
	return opcaoConfig(fich);
}

unsigned int Interacao::lerUInt(string msg) {
	unsigned int valor;
	bool leu = false;

	do {
		cout << msg;
		string s;
		cin >> s;
		istringstream iss(s);
		if (iss >> valor) // se correu bem a leitura
			leu = true;
	} while (!leu);
	return valor;
}
string Interacao::lerNome(string pergunta) {
	string nome;
	cout << pergunta;
	cin.ignore(100, '\n');
	getline(cin, nome);
	return nome;
}
unsigned int Interacao::escolheOpcao(istringstream & iss) {
	string s;
	unsigned int opt = -1;
	iss >> s;
	if (s == "sair")
		opt = 0;
	else if (s == "config")
		opt = 1;
	else if (s == "exec")
		opt = 2;
	else if (s == "prox")
		opt = 3;
	else if (s == "compranav")
		opt = 4;
	else if (s == "vendenav")
		opt = 5;
	else if (s == "lista")
		opt = 6;
	else if (s == "compra")
		opt = 7;
	else if (s == "vende")
		opt = 8;
	else if (s == "move")
		opt = 9;
	else if (s == "auto")
		opt = 10;
	else if (s == "stop")
		opt = 11;
	else if (s == "pirata")
		opt = 12;
	else if (s == "evpos")
		opt = 13;
	else if (s == "evnav")
		opt = 14;
	else if (s == "moedas")
		opt = 15;
	else if (s == "vaipara")
		opt = 16;
	else if (s == "comprasold")
		opt = 17;
	else if (s == "saveg")
		opt = 18;
	else if (s == "loadg")
		opt = 19;
	else if (s == "delg")
		opt = 20;
	else if (s == "help")
		opt = 21;
	else if (s == "vaiparacoords")
		opt = 22;
	
	return opt;
}

string Interacao::perguntaOpcao() {	
	string cmd;
	cout << "\ncomando> ";
	getline(cin, cmd);
	return cmd;
}

void Interacao::opcaoMoverNavio(istringstream &iss) {
	int id;
	string key;
	iss >> id;
	iss >> key;
	if (jogo->moveNavio(id, key))
		cout << "Navio foi movido" << endl;
	else
		cout << "Navio nao foi movido" << endl;
}
bool Interacao::opcaoConfig(string fich) {
	return jogo->le_fich(fich);
}
void Interacao::opcaoCompraNavio(istringstream &iss) {
	char tipo;
	iss >> tipo;
	tipo = toupper(tipo);
	if (jogo->compraNavio(tipo))
		cout << "Acrescentou navio" << endl;
	else
		cout << "Nao acrescentou" << endl;
}
void Interacao::opcaoVendeNavio(istringstream &iss) {
	int id;
	iss >> id;
	if (jogo->vendeNavio(id))
		cout << "Navio " << id << " vendido" << endl;
	else
		cout << "Navio nao foi vendido" << endl;
}
void Interacao::opcaoVendeMercadoria(istringstream &iss) {
	int id;
	iss >> id;
	if (jogo->vendeMercadoria(id))
		cout << "Mercadoria vendida" << endl;
	else
		cout << "Mercadoria nao foi vendida" << endl;
}
void Interacao::opcaoCompraMercadoria(istringstream &iss) {
	int id, quant;
	iss >> id;
	iss >> quant;
	if (jogo->compraMercadoria(id, quant))
		cout << "O navio " << id << " comprou " << " mercadoria" << endl;
	else
		cout << "Mercadoria nao foi comprada" << endl;
}
void Interacao::opcaoDarMoedas(istringstream &iss) {
	int quant;
	iss >> quant;
	jogo->adicionaMoedas(quant);
}
void Interacao::opcaoCompraSoldados(istringstream &iss) {
	int id, quant;
	iss >> id;
	iss >> quant;
	if (jogo->compraSoldados(id, quant))
		cout << "Soldado(s) comprado(s)" << endl;
	else
		cout << "Soldados nao foram comprados" << endl;
}
void Interacao::opcaoScript(istringstream &iss, vector <string> & ordens) {
	string nome_fich, s, cmd;
	int opt;
	iss >> nome_fich;
	
	ifstream fich(nome_fich);
	cout << "Estou a ler " << nome_fich << endl;
	system("pause");
	if (!fich.is_open()) {
		cout << "Ficheiro '" << nome_fich << "' nao existe..." << endl;
		return;
	}
	while (!fich.eof()) {
		getline(fich, s);
		cout << "Comando inserido: " << s << endl;
		cmd = s;
		istringstream le(s);
		opt = escolheOpcao(le);
		if (validaParametros(opt, cmd, le, ordens))
			ordens.push_back(cmd);
	}
	processaOrdens(ordens);
}
void Interacao::opcaoLista(istringstream & iss) {
	cout << "Tabela de precos:" << endl;
	cout << "Comprar Mercadoria: " << jogo->getPrecoCompraMercadoria() << endl;
	cout << "Vende Mercadoria: " << jogo->getPrecoVendaMercadoria() << endl;
	cout << "Compra/Vende Soldados: " << jogo->getPrecoSoldados() << endl;
	cout << "Vende peixe: " << jogo->getPrecoPeixe() << endl;
}
void Interacao::opcaoAcrescentaInimigo(istringstream & iss) {
	int x, y;
	char tipo;
	iss >> x; iss >> y; iss >> tipo;
	tipo = toupper(tipo);
	if (jogo->acrescentaNavioPirata(x, y, tipo))
		cout << "Barco inimigo foi spawnado" << endl;
	else
		cout << "Barco inimigo spawnou destruido" << endl;
}
void Interacao::opcaoAutoGestao(istringstream & iss, int controlo) {
	controlo = 1;
}
void Interacao::opcaoStop(istringstream & iss, int controlo) {
	controlo = 0;
}
void Interacao::opcaoMostraPontuacao() {
	cout << "Pontuacao: " << endl << "O jogador " << jogo->getPlayer() << " teve " << jogo->pontuacao() << " pontos." << endl;
}
string toUpper(string s) {
	string result;
	for (int i = 0; i < s.length(); i++)
		result += toupper(s.at(i));
	return result;
}
bool Interacao::opcaoSegueCoords(istringstream & iss) {
	int id, x, y;
	iss >> id;
	iss >> x;
	iss >> y;
	if (jogo->vaiparacoords(id, x, y)) {
		cout << "Navio chegou ao destino" << endl;
		return true;
	}
	return false;
}
bool Interacao::opcaoSeguePorto(istringstream & iss) {
	int id;
	char porto;
	iss >> id;
	iss >> porto;
	if (jogo->vaiparaporto(id, porto)) {
		cout << "Navio chegou ao porto" << endl;
		return true;
	}
	return false;
}
bool Interacao::stringDigit(string s) {
	for (int i = 0; i < s.length(); i++)
		if (!isdigit(s.at(i)))
			return false;
	return true;
}
bool Interacao::validaParametros(int opt, string cmd, istringstream & iss, vector <string> & ordens) {
	char c;
	int id, quant, x, y;
	string result, aux, s;
	switch (opt) {
	case 4: // compranav
		iss >> c;
		c = toupper(c);
		if (c == 'V' || c == 'E' || c == 'G' || c == 'F' || c == 'S')
			return true;
		else {
			cout << "O navio tem de ser do tipo (V)eleiro, (F)ragata, (G)aleao, (E)scuna ou e(S)pecial." << endl;
			return false;
		}
		break;
	case 5: // vendenav
		iss >> id;
		if (id > 0)
			return true;
		else {
			cout << "O comando deve receber um ID maior que 0" << endl;
			return false;
		}
		break;
	case 6: // lista
		opcaoLista(iss);
		break;
	case 7: // compra mercadoria
		iss >> id;
		iss >> quant;
		if (id > 0 && quant > 0)
			return true;
		else {
			cout << "O comando deve receber um ID e uma quantidade, ambos maiores que 0" << endl;
			return false;
		}
		break;
	case 8: // vende mercadoria
		iss >> id;
		if (id > 0)
			return true;
		else
			cout << "O comando deve receber um ID maior que 0" << endl;
		return false;
		break;
	case 9: // move navio
		iss >> id;
		iss >> aux;
		aux = toUpper(aux);
		if (id > 0 && (aux == "B" || aux == "C" || aux == "D" || aux == "E" || aux == "CE" || aux == "CD" || aux == "BE" || aux == "BD"))
			return true;
		else if (id <= 0)
			cout << "O comando deve receber um ID maior do que 0" << endl;
		else
			cout << "A direcao inserida nao existe! Direcoes validas: (B,C,E,D,BE,BD,CE,CD)" << endl;
		return false;
		break;
	case 12: // cria navio pirata
		iss >> x;
		iss >> y;
		iss >> c;
		c = toupper(c);
		if (x >= 0 && y >= 0 && (c == 'F' || c == 'V'))
			return true;
		else if (x < 0 || y < 0)
			cout << "Coordenas inseridas {" << x << "," << y << "} nao correspondem a coordenadas validas" << endl;
		else
			cout << "Barcos piratas so podem ser do tipo (F)ragata ou (V)eleiro" << endl;
		return false;
		break;
	case 13: // evpos
		iss >> c;
		iss >> x;
		iss >> y;
		c = toupper(c);
		if ((c == 'T' || c == 'C') && x >= 0 && y >= 0)
			return true;
		else if (x < 0 || y < 0)
			cout << "Coordenas inseridas {" << x << "," << y << "} nao correspondem a coordenadas validas" << endl;
		else
			cout << "Eventos so podem ser do tipo (T)empestades ou (C)almarias" << endl;
		return false;
		break;
	case 14: // evnav
		iss >> c;
		iss >> id;
		c = toupper(c);
		if ((c == 'S' || c == 'M') && id > 0)
			return true;
		else if (id < 0)
			cout << "O comando deve receber um ID maior do que 0" << endl;
		else
			cout << "Eventos so podem ser do tipo de (S)ereias ou (M)otins" << endl;
		return false;
		break;
	case 16: // vaipara
		iss >> aux;
		iss >> s;
		if (stringDigit(s))
		{
			result += "vaiparacoords ";
			result += aux;
			result += " ";
			result += s;
			result += " ";
			iss >> s;
			result += s;
			ordens.push_back(result);
		}
		else
			ordens.push_back(cmd);
		return false;
		break;
	case 17: // comprasold
		iss >> id;
		iss >> quant;
		if (id > 0 && quant > 0)
			return true;
		else
			cout << "O comando deve receber um ID e uma quantidade, ambos maiores que 0" << endl;
		return false;
		break;
	case -1:
		return false;
		break;
	}
	return true; // por causa dos comandos que a interacao nao consegue validar
}
void Interacao::opcaoProx(vector <string> & ordens) {
	processaOrdens(ordens);											//Fase 2: Execução dos comandos pendentes/ comportamento automatico
	jogo->processaPesca();
	jogo->movimentoAuto(ordens);
	jogo->resetMoveu();
	jogo->procuraBatalhas();										//Fase 3: Combates 
	jogo->procuraBatalhasPorto();
	jogo->navioSemDono();
	jogo->processaEventos();
	jogo->spawnInimigos();
	jogo->bebeAgua();
	jogo->reporAgua();
	jogo->eliminaDestrocos();
	impLog(jogo->devolveLog());
	jogo->trataLog();
	jogo->eliminaDestrocos();
}
void Interacao::opcaoProx() {
	jogo->processaPesca();
	jogo->resetMoveu();
	jogo->procuraBatalhas();
	jogo->procuraBatalhasPorto();
	jogo->navioSemDono();
	jogo->processaEventos();
	jogo->spawnInimigos();
	jogo->bebeAgua();
	jogo->reporAgua();
}
void Interacao::opcaoCriaEventoCoords(int opt, string cmd, istringstream & iss, vector <string> & ordens) {
	if (validaParametros(opt, cmd, iss, ordens))
	{
		string aux;
		char tipo;
		int x, y;
		istringstream le(cmd);
		le >> aux;
		le >> tipo; le >> x; le >> y;
		jogo->criaEventoCoords(tipo, x, y);
	}
}
void Interacao::opcaoCriaEventoNavio(int opt, string cmd, istringstream & iss, vector <string> & ordens) {
	if (validaParametros(opt, cmd, iss, ordens))
	{
		string aux;
		char tipo;
		int id;
		istringstream le(cmd);
		le >> aux;
		le >> tipo;
		le >> id;
		jogo->criaEventoNav(tipo, id);
	}
}
void Interacao::menu() {
	vector<string> opcoes;
	opcoes.push_back("Sair");
	opcoes.push_back("config <nomeFicheiro>");
	opcoes.push_back("exec <nomeFicheiro>");
	opcoes.push_back("prox");
	opcoes.push_back("compranav <T>");
	opcoes.push_back("vendenav <N>");
	opcoes.push_back("lista");
	opcoes.push_back("compra <N> <M>");
	opcoes.push_back("vende <N>");
	opcoes.push_back("move <N> <X>");
	opcoes.push_back("auto <N>");
	opcoes.push_back("stop <N>");
	opcoes.push_back("pirata <x> <y> <t>");
	opcoes.push_back("evpos <E> <x> <y>");
	opcoes.push_back("evnav <E> <N>");
	opcoes.push_back("moedas <N>");
	opcoes.push_back("vaipara <N> <P>");
	opcoes.push_back("vaipara <N> <x> <y>");
	opcoes.push_back("comprasold <N> <S>");
	opcoes.push_back("saveg <nome>");
	opcoes.push_back("loadg <nome>");
	opcoes.push_back("delg <nome>");

	vector <string> ordens;
	vector <string> script;

	int opcao = -1, controlo = 0;
	string cmd, num, aux, result, s;
	do {
		jogo->mostra_mapa();
		jogo->mostra_navios();

		cmd = perguntaOpcao();
		aux = cmd;
		istringstream iss(aux);
		opcao = escolheOpcao(iss);
		if (opcao == 22)
			opcao = -1;

		switch (opcao) {
		case 0: // sair
			opcaoMostraPontuacao();
			break;
		case 1: // config
			iss >> aux;
			opcaoConfig(aux);
			break;
		case 2: // exec
			opcaoScript(iss, ordens);
			break;
		case 3: // prox
			opcaoProx(ordens);
			break;
		case 4: // compranav
			if (validaParametros(4, cmd, iss, ordens))
				ordens.push_back(cmd);
			break;
		case 5: // vendenav
			if(validaParametros(5, cmd, iss, ordens))
				ordens.push_back(cmd);
			break;
		case 6: // lista
			opcaoLista(iss);
			break;
		case 7: // compra mercadoria
			if(validaParametros(7, cmd, iss, ordens))
				ordens.push_back(cmd);
			break;
		case 8: // vende mercadoria
			if(validaParametros(8, cmd, iss, ordens))
				ordens.push_back(cmd);
			break;
		case 9: // move navio
			if(validaParametros(9, cmd, iss, ordens))
				ordens.push_back(cmd);
			break;
		case 10: // auto-gestao
			opcaoAutoGestao(iss, controlo);
			break;
		case 11: // stop auto-gestao
			opcaoStop(iss, controlo);
			break;
		case 12: // cria navio pirata
			if(validaParametros(12, cmd, iss, ordens))
				ordens.push_back(cmd);
			break;
		case 13: // evpos
			opcaoCriaEventoCoords(13, cmd, iss, ordens);
			break;
		case 14: // evnav
			opcaoCriaEventoNavio(14, cmd, iss, ordens);
			break;
		case 15: // acrescenta moedas
			opcaoDarMoedas(iss);
			break;
		case 16: // vaipara
			if(validaParametros(16, cmd, iss, ordens))
				ordens.push_back(cmd);
			break;
		case 17: // comprasold
			if(validaParametros(17, cmd, iss, ordens))
				ordens.push_back(cmd);
			break;
		case 18: // save
			opcaoSave(iss);
			break;
		case 19: // load
			opcaoLoad(iss);
			break;
		case 20: // del
			opcaoDelete(iss);
			break;
		case 21: // help
			for (unsigned int i = 0; i < opcoes.size(); i++)
				cout << endl << "\t" << i << " - " << opcoes[i];
			cout << endl;
			break;
		case -1:
			cout << "o comando '" << cmd << "' nao existe," << " digite 'help' para conhecer todos os comandos" << endl;
			break;
		}
		system("pause");
	} while (opcao != 0);
}
void Interacao::impVetor(vector <string> ordens) {
	for (int i = 0; i < ordens.size(); i++)
		cout << "ordem: " << ordens[i] << endl;
	system("pause");
}
void Interacao::processaOrdens(vector <string> & ordens) {
	for (auto i = 0; i < ordens.size(); ) {
		istringstream iss(ordens[i]);
		if(executaOrdens(escolheOpcao(iss), iss, ordens))
			ordens.erase(ordens.begin() + i);
		else {
			i++;
		}
	}
} 
bool Interacao::executaOrdens(int opt, istringstream & iss, vector <string> & ordens) {
	string aux;
	switch (opt) {
	case 0:
		opcaoMostraPontuacao();
		return true;
		break;
	case 1: // config
		iss >> aux;
		opcaoConfig(aux);
		return true;
		break;
	case 3: // prox
		opcaoProx();
		return true;
		break;
	case 4:		//compranav
		opcaoCompraNavio(iss);
		return true;
		break;
	case 5:		//vendenav
		opcaoVendeNavio(iss);
		return true;
		break;
	case 6:
		opcaoLista(iss);
		return true;
		break;
	case 7:		//compra mercadoria
		opcaoCompraMercadoria(iss);
		return true;
		break;
	case 8:		// vende mercadoria
		opcaoVendeMercadoria(iss);
		return true;
		break;
	case 9:		//move
		opcaoMoverNavio(iss);
		return true;
		break;
	case 10:
		// opcaoStop(iss, controlo);
		return true;
		break;
	case 11:
		// opcaoAutoGestao(iss, controlo);
		return true;
		break;
	case 12:	//cria pirata
		opcaoAcrescentaInimigo(iss);
		return true;
		break;
	case 13: // evpos
		return true;
		break;
	case 14: // evnav
		return true;
		break;
	case 15: // moedas
		opcaoDarMoedas(iss);
		return true;
		break;
	case 16:	//vaipara porto
		return opcaoSeguePorto(iss);
		break;
	case 17:	//compra sold
		opcaoCompraSoldados(iss);
		return true;
		break;
	case 18: // save
		opcaoSave(iss);
		return true;
		break;
	case 19: // load
		opcaoLoad(iss);
		return true;
		break;
	case 20: // del
		opcaoDelete(iss);
		return true;
		break;
	case 22:	//vaipara coords
		return opcaoSegueCoords(iss);
		break;
	}
	return true;
}
void Interacao::impLog(vector <string> log) {
	for (int i = 0; i < log.size(); i++)
		cout << log[i] << endl;
}
Interacao::~Interacao() {
	delete jogo;
}
void Interacao::opcaoSave(istringstream & iss) {
	string n;
	iss >> n;
	jogo->saveGame(n);
}

void Interacao::opcaoLoad(istringstream & iss) {
	string n;
	iss >> n;
	if (jogo->loadGame(n))
		cout << "O ficheiro " << n << " foi lido corretamente" << endl;
	else
		cout << "O ficheiro " << n << " nao existe" << endl;
}

void Interacao::opcaoDelete(istringstream & iss) {
	string n;
	char str[20];
	iss >> str;
	if (jogo->delGame(str))
		cout << "O ficheiro " << str << " foi apagado com sucesso" << endl;
	else
		cout << "O ficheiro " << str << " nao existe" << endl;
}