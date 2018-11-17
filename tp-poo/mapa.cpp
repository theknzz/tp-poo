#include "mapa.h"
#include <fstream>
#include <sstream>
using namespace std;

int linhas, colunas;

void mostra_mapa(int alt, int larg,vector<Celula> mapa) {
	int cor, tipoCor = 0;							//cor guarda a Consola::(static const int) || tipoCor =0 em linhas impares, e =1 em linhas pares
	int a, l, i, j;
	for (a = 0;a < alt; a++) {
		if (tipoCor == 0)							//define a primeira cor a usar na linha, tendo em conta se é par ou impar
			cor = Consola::VERMELHO;
		else
			cor = Consola::VERMELHO_CLARO;
		for (i = 0;i < 2;i++) {						//prepara para escrever a mesma linha 2x, uma vez que cada celula é representada em 2x2
			for (l = 0;l < larg; l++) {
				Consola::setBackgroundColor(cor);
				for (j = 0;j < 2;j++) {				//prepara para escrever a mesma célula 2x, uma vez que cada célula é representada em 2x2
					cout << mapa[a*larg + l];
				}
				if (cor == Consola::VERMELHO) {		//troca a cor, para fazer padrao xadrez durante a linha
					cor = Consola::VERMELHO_CLARO;
				}
				else {
					cor = Consola::VERMELHO;
				}
			}
			cout << endl;
		}
		if (tipoCor == 0)							//troca tipoCor, o que definirá a cor inicial da próxima linha para manter padrao xadrez
			tipoCor = 1;
		else
			tipoCor = 0;
	}
	Consola::setBackgroundColor(Consola::PRETO);
}

vector<Celula> le_mapa()
{
	vector<Celula> cel;
	string nome_fich;
	cout << "Nome do fich: ";
	cin >> nome_fich;
	char ch;
	string str;
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

	// DEBUG 
		cout << "LINHAS: " << linhas << "\nCOLUNAS: " << colunas << endl;
	
	for(auto i = 0 ; i < linhas; i++)
	{
		for (auto j = 0; j < colunas; j++)
		{
			fich >> ch;

			Celula a(linhas, colunas, ch);
			cel.push_back(a);
			cout << a.getTipo();
		}
		cout << "\n";
	}
	return cel;
}