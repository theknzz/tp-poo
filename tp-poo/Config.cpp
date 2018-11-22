#include "Config.h"
#include "Celula.h"

#include <iostream>
#include <fstream>
#include <sstream>

// DEFINICAO DAS VARIAVEIS GLOBAIS
int linhas, colunas, moedas, probpirata, preconavio, precosoldado, precovendpeixe, precocompmercad, precovendmercad, soldadosporto, probevento, probtempestade, probsereias, probcalmaria, probmotim;

void var(string var, istringstream &le)
{
	int value;

	if (var == "moedas") {
		le >> value;
		moedas = value;
	}
	else if (var == "probpirata") {
		le >> value;
		probpirata = value;
	}
	else if (var == "preconavio") {
		le >> value;
		preconavio = value;
	}
	else if (var == "precosoldado") {
		le >> value;
		precosoldado = value;
	}
	else if (var == "precovendpeixe") {
		le >> value;
		precovendpeixe = value;
	}
	else if (var == "precocompmercad") {
		le >> value;
		precocompmercad = value;
	}
	else if (var == "precovendmercad") {
		le >> value;
		precovendmercad = value;
	}
	else if (var == "soldadosporto") {
		le >> value;
		soldadosporto = value;
	}
	else if (var == "probevento") {
		le >> value;
		probevento = value;
	}
	else if (var == "probtempestade") {
		le >> value;
		probtempestade = value;
	}
	else if (var == "probsereias") {
		le >> value;
		probsereias = value;
	}
	else if (var == "probcalmaria") {
		le >> value;
		probcalmaria = value;
	}
	else if (var == "probmotim") {
		le >> value;
		probmotim = value;
	}
}


vector<Celula> le_fich()
{
	char ch;
	string str;
	vector<Celula> cel;

	string nome_fich;

	cout << "Nome do fich: ";
	cin >> nome_fich;
	ifstream fich(nome_fich);

	for (auto i = 0; i < 2; i++)
	{
		getline(fich, str);
		istringstream iss(str);
		iss >> str;
		if (str == "linhas")
			iss >> linhas;
		else
			iss >> colunas;
	}


	for (auto i = 0; i < linhas; i++)
	{
		for (auto j = 0; j < colunas; j++)
		{
			fich >> ch;
			Celula a(j, i, ch);
			cel.push_back(a);
		}
	}

	// apanhar o enter
	getline(fich, str);
	
	while (!fich.eof())
	{
		getline(fich, str);
		istringstream le(str);
		le >> str;
		var(str, le);

		if (str.empty())
			break;
	}

	fich.close();

	return cel;
}