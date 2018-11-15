#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>


using namespace std;

vector<vector <char>> le_fich(istream& fich)
{
	int colunas, linhas;
	string tipo;

	vector<vector <char>> mapa;
	fich >> tipo >> linhas;
	fich >> tipo >> colunas;

	cout << "LINHAS :" << linhas << endl;
	cout << "COLUNAS :" << colunas << endl;

	// le o mapa para vetor
	for(int i = 0; i < linhas; i++)
	{
		string aux;
		//fich >> aux;


		//mapa.push_back(aux);
		getline(fich, aux);

		vector<char> temp;

		for (int j = 0; j < colunas; j++)
		{
			temp.push_back(aux[j]);
		}

		mapa.push_back(temp);
	
	}


	// mostra o mapa
	for(int i = 0; i < linhas; i++)
	{
		for(int j = 0 ; j < colunas; j++)
			cout << mapa[i][j] << endl;
	}

	// em caso de erro: valores default
	if(fich.fail())
	{
		linhas = 20;
		colunas = 10;
	}

	// free??
	fich.clear();

	return mapa;
}
