#include "Comandos.h"
#include "Jogador.h"
#include "Utils.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void Comandos::menu()const
{
	string lixo;
	string na;
	cout << "\nNome Jogador: ";
	getline(cin, na);

	Jogador jogador(100,na); // jogador iniciado com 100 moedas
	
	cin.ignore(100,'\n');

	while(1)
		{
			string comando;
			cout << "Comando: ";
			getline(cin, comando);

			istringstream iss(comando);
			iss >> comando;
			
			const auto opt = Utils::menu_opt(comando);

			// verificao de inputs
			if (opt == 0) 
				return;
			else if(opt == -1)
				cout << "COMANDO: " << comando << " nao existe! " << endl;
			else if (opt == -2)
				cout << "Insira um comando..." << endl;

			Utils::opt(opt, &iss, jogador);

			if (opt == 1) // exec
			{
				string nome_fich, cmd;
				iss >> nome_fich;
				// abre o ficheiro
				ifstream f(nome_fich);

				if(!f.is_open()) {
					cout << "Ficheiro nao existe..." << endl;
					return;
				}
				while (!f.eof())
				{
					// le a linha do ficheiro
					getline(f, cmd);

					// le palavra até ao espaço e guarda a em 'cmd'
					istringstream le(cmd);

					// le o comando
					le >> cmd;
					
					const auto op = Utils::menu_opt(cmd);
					
					// procura o comando e executa o
					Utils::opt(op, &le, jogador);
				}

				f.close();
			}
		}
}