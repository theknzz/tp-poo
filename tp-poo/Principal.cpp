#include <vector>
#include "Comandos.h"
#include "Consola.h"
#include "Navio.h"
#include "Utils.h"
#include "Tipo_Navio.h"
#include "Celula.h"
#include "mapa.h"


int main()
{
	Comandos c;
	string fich;

		//cout << "######                                        #####                                     " << endl;
		//cout << "#     #  #####     ##    #    #  ######      #     #    ##    #  #        ####   #####  " << endl;
		//cout << "#     #  #    #   #  #   #    #  #           #         #  #   #  #       #    #  #    # " << endl;
		//cout << "######   #    #  #    #  #    #  #####        #####   #    #  #  #       #    #  #    # " << endl;
		//cout << "#     #  #####   ######  #    #  #                 #  ######  #  #       #    #  #####  " << endl;
		//cout << "#     #  #   #   #    #   #  #   #           #     #  #    #  #  #       #    #  #   #  " << endl;
		//cout << "######   #    #  #    #    ##    ######       #####   #    #  #  ######   ####   #    # \n\n" << endl;

	//c.menu();

	auto cel = le_mapa();
	//mostra_mapa(20,10,cel);
	system("pause");
}
