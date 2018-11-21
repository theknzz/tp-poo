#include <vector>
#include "Comandos.h"
#include "Consola.h"
#include "mapa.h"
#include <iostream>

int main()
{
	Comandos c;
	Jogador jogador(100); // jogador iniciado com 100 moedas

		//cout << "######                                        #####                                     " << endl;
		//cout << "#     #  #####     ##    #    #  ######      #     #    ##    #  #        ####   #####  " << endl;
		//cout << "#     #  #    #   #  #   #    #  #           #         #  #   #  #       #    #  #    # " << endl;
		//cout << "######   #    #  #    #  #    #  #####        #####   #    #  #  #       #    #  #    # " << endl;
		//cout << "#     #  #####   ######  #    #  #                 #  ######  #  #       #    #  #####  " << endl;
		//cout << "#     #  #   #   #    #   #  #   #           #     #  #    #  #  #       #    #  #   #  " << endl;
		//cout << "######   #    #  #    #    ##    ######       #####   #    #  #  ######   ####   #    # \n\n" << endl;

	// le_mapa -> vector / bool
	auto const mapa = le_mapa();
	c.menu(jogador, mapa);
	system("pause");
}
