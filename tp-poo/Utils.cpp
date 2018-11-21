#include <iostream>
#include <fstream>
#include <vector>
#include <iostream>
#include <cctype>

#include "Utils.h"
#include "Jogador.h"
#include "Navio.h"

using namespace std;

//int ver = 0;

auto const preconavio = 10;
auto const moedas = 100;

//Utils::Utils(string nome)
//{
//	auto ver = false;
//	string str, lixo, var;
//	int linhas, colunas;
//
//	ifstream fich(nome);
//
//	getline(cin, str);
//	istringstream iss(str);
//	iss >> str;
//
//	if (str == "linhas")
//		iss >> linhas;
//	else
//		iss >> colunas;
//
//	// fseek dos burros
//	for (auto i = 0; i < linhas; i++)
//		getline(cin, lixo);
//
//	while (ver == false){
//		getline(cin, var);
//		istringstream le(var);
//		le >> var;
//		ver = le_vars(&le, var);
//	}
//}	

//bool Utils::le_vars(istringstream *le,string var)
//{
//	if (var == "moedas"){
//		*le >> atoi(moedas);
//		ver++;
//	}
//	else if (var == "probpirata") {
//		*le >> probpirata;
//		ver++;
//	}
//	else if (var == "preconavio") {
//		*le >> preconavio;
//		ver++;
//	}
//	else if (var == "precosoldado") {
//		*le >> precosoldado;
//		ver++;
//	}
//	else if (var == "precovendpeixe") {
//		*le >> precovendpeixe;
//		ver++;
//	}
//	else if (var == "precocompmercad") {
//		*le >> precompmercad;
//		ver++;
//	}
//	else if (var == "precovendmercad") {
//		*le >> precovendemercad;
//		ver++;
//	}
//	else if (var == "soldadosporto") {
//		*le >> soldadosporto;
//		ver++;
//	}
//	else if (var == "probevento") {
//		*le >> probevento;
//		ver++;
//	}
//	else if (var == "probtempestade") {
//		*le >> probtempestade;
//		ver++;
//	}
//	else if (var == "probsereias") {
//		*le >> probsereias;
//		ver++;
//	}
//	else if (var == "probcalmaria") {
//		*le >> probcalmaria;
//		ver++;
//	}
//	else if (var == "probmotim") {
//		*le >> probmotim;
//		ver++;
//	}
//
//	if (ver == 13)
//		return true;
//	else
//		return false;
//}

int Utils::menu_opt(string s)
{
	auto opt = -1;

	if (s == "exec")
	{
		opt = 1;
	}
	else if (s == "prox")
	{
		opt = 2;
	}
	else if (s == "compranav")
	{
		opt = 3;
	}
	else if (s == "vendenav")
	{
		opt = 4;
	}
	else if (s == "lista")
	{
		opt = 5;
	}
	else if (s == "compra")
	{
		opt = 6;
	}
	else if (s == "vende")
	{
		opt = 7;
	}
	else if (s == "move")
	{
		opt = 8;
	}
	else if (s == "auto")
	{
		opt = 9;
	}
	else if (s == "stop")
	{
		opt = 10;
	}
	else if (s == "pirata")
	{
		opt = 11;
	}
	else if (s == "evpos")
	{
		opt = 12;
	}
	else if (s == "evnav")
	{
		opt = 13;
	}
	else if (s == "moedas")
	{
		opt = 14;
	}
	else if (s == "vaipara") // atencao que existem dois
	{
		opt = 15;
	}
	else if (s == "vaiparav2")
	{
		opt = 16;
	}
	else if (s == "comprasold")
	{
		opt = 17;
	}
	else if (s == "saveg")
	{
		opt = 18;
	}
	else if (s == "loadg")
	{
		opt = 19;
	}
	else if (s == "delg")
	{
		opt = 20;
	}
	else if (s == "sair")
	{
		opt = 0;
	}
	else if (s.empty())
		opt = -2;

	return opt;
}

int Utils::opt(int opt, istringstream *iss, Jogador &jogador)
{
	switch (opt)
	{
	case 2: // prox
		cout << "prox..." << endl;
		break;
	
	case 3: // compranav <T>

		
		char tipo;
		*iss >> tipo;
		
		// garantir que nao ha erros
		tipo = toupper(tipo); 
		
		switch (tipo)
		{
		case 'V': // veleiro
			if (jogador.getmoedas() >= preconavio) {
				
				auto* x = new Navio (tipo, preconavio, 200, 0, 40, 0, 0);
				jogador.pagar(preconavio);
				jogador.addNavio(x);
				cout << "Moedas: " << jogador.getmoedas() << endl;
			}
			else
				cout << "Moedas insuficientes...\n" << "O jogador tem " << jogador.getmoedas() << " moedas e sao precisas " << preconavio << " moedas" << endl;
			break;

		case 'G': //galeao
			if (jogador.getmoedas() >= preconavio)
			{
				auto* x = new Navio(tipo, preconavio, 400, 0, 70, 0, 0);
				jogador.pagar(preconavio);
				jogador.addNavio(x);
				cout << "Moedas: " << jogador.getmoedas() << endl;
			}
			else
				cout << "Moedas insuficientes...\n" << "O jogador tem " << jogador.getmoedas() << " moedas e sao precisas " << preconavio << " moedas" << endl;
			break;

		case 'E': // escuna
			if (jogador.getmoedas() >= preconavio)
			{
				auto* x = new Navio(tipo, preconavio, 100, 0, 20, 0, 0);
				jogador.pagar(preconavio);
				jogador.addNavio(x);
				cout << "Moedas: " << jogador.getmoedas() << endl;
			}
			else
				cout << "Moedas insuficientes...\n" << "O jogador tem " << jogador.getmoedas() << " moedas e sao precisas " << preconavio << " moedas" << endl;
			break;

		case 'F': // fragata
			if (jogador.getmoedas() >= preconavio)
			{
				auto* x = new Navio(tipo, preconavio, 500, 0, 0, 0, 0);
				jogador.pagar(preconavio);
				jogador.addNavio(x);
				cout << "Moedas: " << jogador.getmoedas() << endl;
			}
			else
				cout << "Moedas insuficientes...\n" << "O jogador tem " << jogador.getmoedas() << " moedas e sao precisas " << preconavio << " moedas" << endl;
			break;

		case 'R': // especial
			cout << "Especial" << endl;
			break;

		default:
				cout << "[ERRO] Tipo: " << "<" << tipo << "> nao existe \n" << "COMANDO : compranav <V/G/E/F/R> " << endl;
			break;
		}
		break;

	case 4: // vendenav <T>
		cout << "Navio vendido!" << endl;
		break;
	case 5: // lista
		cout << "lista!" << endl;
		break;
	case 6: // compra <N> <M>
		cout << "compra!" << endl;
		break;
	case 7: // vende <N>
		cout << "vende !" << endl;
		break;
	case 8: // move <N> <X>
		cout << "move!" << endl;
		break;
	case 9: // auto <N>
		cout << "auto!" << endl;
		break;
	case 10: // stop <N>
		cout << "stop!" << endl;
		break;
	case 11: // pirata <x> <y> <T>
		cout << "pirata!" << endl;
		break;
	case 12: // evpos <E> <x> <y>
		cout << "evpos!" << endl;
		break;
	case 13: // evnav <E> <N>
		cout << "evnav" << endl;
		break;
	case 14: // moedas <N>
		cout << "moedas" << endl;
		break;
	case 15: // vaipara <N> <x> <y>
		cout << "vaipara" << endl;
		break;
	case 16: // vaipara 2 <N> <P>
		cout << "vaipara_v2" << endl;
		break;
	case 17: // comprasold <N> <S>
		cout << "comprasold" << endl;
		break;
	case 18: // saveg <nome>
		cout << "saveg" << endl;
		break;
	case 19: // loadg <nome>
		cout << "loadg" << endl;
		break;
	case 20: // delg <nome>
		cout << "delg" << endl;
		break;
	case 0: // sair
		cout << "SHUTING DOWN!" << endl;
		break;
	default:
		break;
	}
	return opt;
}


