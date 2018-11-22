#include "Comandos.h"
#include "mapa.h"
#include "Config.h"
#include "Jogador.h"
#include <iostream>

// VARIAVEIS GLOBAIS
extern int linhas, colunas, moedas, probpirata, preconavio, precosoldado, precovendpeixe, precocompmercad, precovendmercad, soldadosporto, probevento, probtempestade, probsereias, probcalmaria, probmotim;

int main()
{
	Comandos c;
	auto const mapa = le_fich();
	Jogador jogador(moedas);

		//cout << "######                                        #####                                     " << endl;
		//cout << "#     #  #####     ##    #    #  ######      #     #    ##    #  #        ####   #####  " << endl;
		//cout << "#     #  #    #   #  #   #    #  #           #         #  #   #  #       #    #  #    # " << endl;
		//cout << "######   #    #  #    #  #    #  #####        #####   #    #  #  #       #    #  #    # " << endl;
		//cout << "#     #  #####   ######  #    #  #                 #  ######  #  #       #    #  #####  " << endl;
		//cout << "#     #  #   #   #    #   #  #   #           #     #  #    #  #  #       #    #  #   #  " << endl;
		//cout << "######   #    #  #    #    ##    ######       #####   #    #  #  ######   ####   #    # \n\n" << endl;

	

	mostra_mapa(linhas, colunas, mapa);
	cout << "Moedas: " << moedas << endl;
	c.menu(jogador, mapa);


}
