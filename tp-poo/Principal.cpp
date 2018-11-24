#include "Comandos.h"
#include "mapa.h"
#include "Config.h"
#include "Jogador.h"
#include <iostream>

int main()
{
	Config cfg;
	Comandos c;
	auto const mapa = le_fich(cfg);
	Jogador jogador(cfg.moedas);
	

		//cout << "######                                        #####                                     " << endl;
		//cout << "#     #  #####     ##    #    #  ######      #     #    ##    #  #        ####   #####  " << endl;
		//cout << "#     #  #    #   #  #   #    #  #           #         #  #   #  #       #    #  #    # " << endl;
		//cout << "######   #    #  #    #  #    #  #####        #####   #    #  #  #       #    #  #    # " << endl;
		//cout << "#     #  #####   ######  #    #  #                 #  ######  #  #       #    #  #####  " << endl;
		//cout << "#     #  #   #   #    #   #  #   #           #     #  #    #  #  #       #    #  #   #  " << endl;
		//cout << "######   #    #  #    #    ##    ######       #####   #    #  #  ######   ####   #    # \n\n" << endl;



	mostra_mapa(cfg, mapa);
	cout << "Moedas: " << jogador.getMoedas() << endl;
	c.menu(jogador, mapa, cfg);

}