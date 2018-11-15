#include <fstream>
#include <vector>
#include "Comandos.h"
#include "Consola.h"
#include "Navio.h"
#include "utils.h"


int Navio::conta = 0;

int main()
{
	Comandos c;
	string fich;
	//Navio('t', 100, 2000, 20, 5, 20, 20);
	//Navio('t', 100, 2000, 20, 5, 20, 20);
	//Navio('t', 100, 2000, 20, 5, 20, 20);

	//// obtem o nome do fich
	//cout << "Fich: ";
	//cin >> fich;

	//// abre o ficheiro
	//ifstream f(fich);
	//vector<vector <char>> mapa = le_fich(f);

	//f.close();

	c.menu();

	system("pause");
}