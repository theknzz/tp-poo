#include <vector>
#include "Comandos.h"
#include "Consola.h"
#include "mapa.h"

int main()
{
	Comandos c;

		//cout << "######                                        #####                                     " << endl;
		//cout << "#     #  #####     ##    #    #  ######      #     #    ##    #  #        ####   #####  " << endl;
		//cout << "#     #  #    #   #  #   #    #  #           #         #  #   #  #       #    #  #    # " << endl;
		//cout << "######   #    #  #    #  #    #  #####        #####   #    #  #  #       #    #  #    # " << endl;
		//cout << "#     #  #####   ######  #    #  #                 #  ######  #  #       #    #  #####  " << endl;
		//cout << "#     #  #   #   #    #   #  #   #           #     #  #    #  #  #       #    #  #   #  " << endl;
		//cout << "######   #    #  #    #    ##    ######       #####   #    #  #  ######   ####   #    # \n\n" << endl;

	// le_mapa -> vector / bool
	auto const mapa = le_mapa();
	mostra_mapa(10, 20, mapa);
	c.menu();
	system("pause");
}
