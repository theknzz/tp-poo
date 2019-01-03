#include "Interacao.h"
#include "Jogo.h"
#include "Jogador.h"

#include <iostream>

using namespace std;


int main() {
	int dificuldade;
	srand(time(NULL));
	string nome;
	cout << "Jogador: ";
	getline(cin, nome);
	do {
		cout << "Dificuldade:\n > [1]Facil\n > [2]Dificil" << endl;
		cin >> dificuldade;
	} while (dificuldade != 2 && dificuldade != 1);
	cin.ignore(100, '\n');
	Jogador * player = new Jogador(nome);
	Jogo * jogo = new Jogo(player, dificuldade);
	Interacao interacao(jogo);
	while(!interacao.inicia());
	interacao.menu();
	delete jogo;
}