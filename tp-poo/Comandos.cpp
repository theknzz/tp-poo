#include "Comandos.h"
#include "Utils.h"

#include <fstream>
#include <iostream>

bool Comandos::menu()const
{
	string comando;
	cout << "Comando: ";
	getline(cin, comando);

	istringstream iss(comando);
	iss >> comando;

	int opt = Utils::menu_opt(comando);

	if (opt == 1) // exec
	{
		string nome_fich, cmd;
		iss >> nome_fich;
		// abre o ficheiro
		ifstream f(nome_fich);
		while(!f.eof())
		{
			cout << "estou dentro do ficheiro" << endl;
			// le a linha do ficheiro
			getline(f, cmd);
			istringstream le(cmd);
			// le o comando
			le >> cmd;
			int op = Utils::menu_opt(cmd);
			// procura o comando e executa o
			Utils::opt(op);
		}
		f.close();
	}

	Utils::opt(opt);

	return false;
}