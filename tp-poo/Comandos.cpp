#include "Comandos.h"
#include "Jogador.h"
#include "Utils.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

bool Comandos::menu()const
{
	Jogador jogador(100); // jogador iniciado com 100 moedas
	string comando;

	while(true)
		{
			cout << "Comando: ";
			getline(cin, comando);

			istringstream iss(comando);
			iss >> comando;


			const auto opt = Utils::menu_opt(comando);

			// verificao de inputs
			if (opt == 0)
				return false;
			else if (opt == -1)
				cout << "COMANDO: " << comando << " nao existe! " << endl;
			else if (opt == -2)
				cout << "Insira um comando..." << endl;

			if (opt == 1) // exec
			{
				string nome_fich, cmd;
				iss >> nome_fich;
				// abre o ficheiro
				ifstream f(nome_fich);
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
					Utils::opt(op, &le, &jogador);
				}
				f.close();
			}
			Utils::opt(opt, &iss, &jogador);
		}
}