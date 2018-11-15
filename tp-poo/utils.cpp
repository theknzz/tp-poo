#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include "utils.h"


using namespace std;

//vector<vector <char>> Utils::le_fich(istream& fich)
//{
//	int colunas, linhas;
//	string tipo;
//
//	vector<vector <char>> mapa;
//	fich >> tipo >> linhas;
//	fich >> tipo >> colunas;
//
//	cout << "LINHAS :" << linhas << endl;
//	cout << "COLUNAS :" << colunas << endl;
//
//	// le o mapa para vetor
//	for(int i = 0; i < linhas; i++)
//	{
//		string aux;
//		//fich >> aux;
//
//
//		//mapa.push_back(aux);
//		getline(fich, aux);
//
//		vector<char> temp;
//
//		for (int j = 0; j < colunas; j++)
//		{
//			temp.push_back(aux[j]);
//		}
//
//		mapa.push_back(temp);
//	
//	}
//
//
//	// mostra o mapa
//	for(int i = 0; i < linhas; i++)
//	{
//		for(int j = 0 ; j < colunas; j++)
//			cout << mapa[i][j] << endl;
//	}
//
//	// em caso de erro: valores default
//	if(fich.fail())
//	{
//		linhas = 20;
//		colunas = 10;
//	}
//
//	// free??
//	fich.clear();
//
//	return mapa;
//}

int Utils::menu_opt(string s)
{
	int opt = 0;

	if(s == "exec")
	{
		opt = 1;
	}
	else if(s == "prox")
	{
		opt = 2;
	}
	else if(s == "compranav")
	{
		opt = 3;
	}
	else if(s == "vendenav")
	{
		opt = 4;
	}
	else if(s == "lista")
	{
		opt = 5;
	}
	else if(s == "compra")
	{
		opt = 6;
	}
	else if(s == "vende")
	{
		opt = 7;
	}
	else if(s == "move")
	{
		opt = 8;
	}
	else if(s == "auto")
	{
		opt = 9;
	}
	else if(s == "stop")
	{
		opt = 10;
	}
	else if(s == "pirata")
	{
		opt = 11;
	}
	else if(s == "evpos")
	{
		opt = 12;
	}
	else if(s == "evnav")
	{
		opt = 13;
	}
	else if(s == "moedas")
	{
		opt = 14;
	}
	else if(s == "vaipara") // atencao que existem dois
	{
		opt = 15;
	}
	else if(s == "comprasold")
	{
		opt = 16;
	}
	else if(s == "saveg")
	{
		opt = 17;
	}
	else if(s == "loadg")
	{
		opt = 18;
	}
	else if(s == "delg")
	{
		opt = 19;
	}
	else if(s == "sair")
	{
		opt = 20;
	}

	return opt;
}

int Utils::opt(int opt)
{
	switch (opt)
	{
	case 2: // prox
		cout << "ola! eu sou o prox" << endl;
 		break;
	case 3: // compranav

		break;
	case 4: // vendenav

		break;
	case 5: // lista

		break;
	case 6: // compra
		cout << "ola eu sou o compra!" << endl;
		break;
	case 7: // vende

		break;
	case 8: // move

		break;
	case 9: // auto

		break;
	case 10: // stop

		break;
	case 11: // pirata

		break;
	case 12: // evpos

		break;
	case 13: // evnav

		break;
	case 14: // moedas

		break;
	case 15: // vaipara

		break;
	case 16: // vaipara 2

		break;
	case 17: // comprasold

		break;
	case 18: // saveg

		break;
	case 19: // loadg

		break;
	case 20: // delg

		break;
	case 21: // sair

		break;

	}
	return opt;
}