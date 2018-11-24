#include "Config.h"
#include "Celula.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include "Jogador.h"


void var(string var, istringstream &le, Config& cfg)
{
	int value;

	if (var == "moedas") {
		le >> value;
		cfg.moedas = value;
	}
	else if (var == "probpirata") {
		le >> value;
		cfg.probpirata = value;
	}
	else if (var == "preconavio") {
		le >> value;
		cfg.preconavio = value;
	}
	else if (var == "precosoldado") {
		le >> value;
		cfg.precosoldado = value;
	}
	else if (var == "precovendpeixe") {
		le >> value;
		cfg.precovendpeixe = value;
	}
	else if (var == "precocompmercad") {
		le >> value;
		cfg.precocompmercad = value;
	}
	else if (var == "precovendmercad") {
		le >> value;
		cfg.precovendmercad = value;
	}
	else if (var == "soldadosporto") {
		le >> value;
		cfg.soldadosporto = value;
	}
	else if (var == "probevento") {
		le >> value;
		cfg.probevento = value;
	}
	else if (var == "probtempestade") {
		le >> value;
		cfg.probtempestade = value;
	}
	else if (var == "probsereias") {
		le >> value;
		cfg.probsereias = value;
	}
	else if (var == "probcalmaria") {
		le >> value;
		cfg.probcalmaria = value;
	}
	else if (var == "probmotim") {
		le >> value;
		cfg.probmotim = value;
	}
}


vector<Celula> le_fich(Config& cfg, Jogador & jogador)
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
			iss >> cfg.linhas;
		else
			iss >> cfg.colunas;
	}


	for (auto i = 0; i < cfg.linhas; i++)
	{
		for (auto j = 0; j < cfg.colunas; j++)
		{
			fich >> ch;

			if (ch != '.' && ch != '+')
			{
				Porto * pt;
				auto ver = isupper(ch);
				if (ver == 0)
				{
					Porto x(ch,j,i);
					pt = &x;
					jogador.addPorto(pt);
				}
				else
				{
					Porto x(ch,j,i);
					pt = &x;
					jogador.addPorto(pt);
				}
			}
			else
			{
				Celula a(j, i, ch);
				cel.push_back(a);
			}
		}
	}

	// apanhar o enter
	getline(fich, str);

	while (!fich.eof())
	{
		getline(fich, str);
		istringstream le(str);
		le >> str;
		var(str, le, cfg);

		if (str.empty())
			break;
	}

	fich.close();

	return cel;
}