#include "Comandos.h"


bool Comandos::menu()const
{
	string comando;
	cout << "Comando: ";
	getline(cin, comando);

	istringstream iss(comando);
	iss >> comando;

	
}