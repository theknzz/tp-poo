#include <fstream>
#include <vector>
#include "Comandos.h"
#include "Consola.h"
#include "Navio.h"
#include "utils.h"
#include "Tipo_Navio.h"
#include "Celula.h"
#include "mapa.h"


int main()
{
	Comandos c;
	string fich;

	//c.menu();

	vector<Celula> cel;
	le_mapa(cel);
	mostra_mapa(20,10,cel);
	system("pause");
}
