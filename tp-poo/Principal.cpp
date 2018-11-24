#include "Comandos.h"
#include "mapa.h"
#include "Config.h"
#include "Jogador.h"

#include <iostream>

int main()
{
	Config cfg;
	Comandos c;

	//cout << "######                                        #####                                     " << endl;
	//cout << "#     #  #####     ##    #    #  ######      #     #    ##    #  #        ####   #####  " << endl;
	//cout << "#     #  #    #   #  #   #    #  #           #         #  #   #  #       #    #  #    # " << endl;
	//cout << "######   #    #  #    #  #    #  #####        #####   #    #  #  #       #    #  #    # " << endl;
	//cout << "#     #  #####   ######  #    #  #                 #  ######  #  #       #    #  #####  " << endl;
	//cout << "#     #  #   #   #    #   #  #   #           #     #  #    #  #  #       #    #  #   #  " << endl;
	//cout << "######   #    #  #    #    ##    ######       #####   #    #  #  ######   ####   #    # \n\n" << endl;

	cout << "Mapas Disponiveis: \n" << "\t > mapa.txt\n" << "\t > cercado.txt\n" << "\t > mar.txt\n" << endl;
	Jogador jogador(cfg.moedas);
	auto mapa = le_fich(cfg, jogador);
	//cout << "Coords: (" << jogador.getPrin_x() << ";" << jogador.getPrin_y() << ")" << endl;

	mostra_mapa(cfg, mapa);
	//cout << "Moedas: " << jogador.getMoedas() << endl;
	c.menu(jogador, mapa, cfg);

}


