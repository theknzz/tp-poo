#include "mapa.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "Consola.h"

using namespace std;

int linhas, colunas;
void mostra_mapa(int alt, int larg,vector<Celula> mapa) {
	int cor;
	bool claro, tipoCor = 0; //cor guarda a Consola::(static const int) || tipoCor =0 em linhas impares, e =1 em linhas pares
	int a, l, i, j;
	Consola::clrscr();
	Consola::setTextColor(Consola::BRANCO_CLARO);
	for (a = 0;a < alt; a++) {
		if (tipoCor == 0)  //define a primeira cor a usar na linha, tendo em conta se e par ou impar
			claro = 0;
		else
			claro = 1;
		for (i = 0;i < 2;i++) {						//prepara para escrever a mesma linha 2x, uma vez que cada celula e representada em 2x2
			for (l = 0;l < larg; l++) {

				if (mapa[a*larg + l].getTipo() == '.')
				{
					if (claro == 0)
						cor = Consola::AZUL;
					else
						cor = Consola::AZUL_CLARO;
				}
				else if (mapa[a*larg + l].getTipo() == '+') {
					if (claro == 0)
						cor = Consola::VERDE;
					else
						cor = Consola::VERDE_CLARO;
				}
				else {
					if (claro == 0)
						cor = Consola::VERMELHO;
					else
						cor = Consola::VERMELHO_CLARO;
				}
				Consola::setBackgroundColor(cor);
				for (j = 0;j < 2;j++) {				//prepara para escrever a mesma celula 2x, uma vez que cada celula e representada em 2x2
					cout << mapa[a*larg + l].getTipo();
				}
				if (claro == 0) {		//troca a cor, para fazer padrao xadrez durante a linha
					claro = 1;
				}
				else {
					claro = 0;
				}
			}
			Consola::setBackgroundColor(Consola::PRETO);
			Consola::setTextColor(Consola::PRETO);
			cout <<'|'<<endl;
			Consola::setTextColor(Consola::BRANCO_CLARO);
		}
		if (tipoCor == 0)							//troca tipoCor, o que definira a cor inicial da proxima linha para manter padrao xadrez
			tipoCor = 1;
		else
			tipoCor = 0;
	}
	Consola::setBackgroundColor(Consola::PRETO);
	Consola::setTextColor(Consola::BRANCO);
}

void mostra_navios(int alt, int larg, const Jogador& jog) {
	for (int i = 0;i < jog.GetnNavios();i++) {
		Consola::gotoxy(jog.getNavio(i)->get_x() * 2, jog.getNavio(i)->get_y() * 2 + 1);
		if ((jog.getNavio(i)->get_x() + jog.getNavio(i)->get_y()) % 2 == 0)
			Consola::setBackgroundColor(Consola::AZUL);
		else
			Consola::setBackgroundColor(Consola::AZUL_CLARO);
		cout << jog.getNavio(i)->get_id();
	}
	Consola::gotoxy(0, alt * 2 + 1);
	Consola::setBackgroundColor(Consola::PRETO);
}

vector<Celula> le_mapa()
{
	char ch;
	string str;
	vector<Celula> cel;

	string nome_fich;

	cout << "Nome do fich: ";
	cin >> nome_fich;
	ifstream fich(nome_fich);

	for (auto i = 0; i < 2; i++)
	{
		getline(fich, str);
		istringstream iss(str);
		iss >> str;
		if (str == "linhas")
			iss >> linhas;
		else
			iss >> colunas;
	}

	// DEBUG cout << "LINHAS: " << linhas << "\nCOLUNAS: " << colunas << endl;
	
	for(auto i = 0 ; i < linhas; i++)
	{
		for (auto j = 0; j < colunas; j++)
		{
			fich >> ch;

			Celula a(j, i, ch);
			cel.push_back(a);
		}
	}
	fich.close();
	return cel;
}