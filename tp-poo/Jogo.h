#ifndef __JOGO__
#define __JOGO__

#include <cctype>

#include "Config.h"
#include "Celula.h"
#include "Tempestade.h"
#include "Sereias.h"
#include "Calmaria.h"
#include "Motim.h"

class Navio;
class Porto;

class Jogo {
	int dificuldade;
	Jogador * jogador;
	vector <Celula> mapa;
	vector <Navio*> navios;
	vector <Navio*> naviosInimigos;
	vector <Navio*> naviosDeriva;
	vector <Porto*> portos;
	vector <Porto*> portosInimigos;
	Config config;
	Evento* evento;
	vector <string> log;
public:
	Jogo(Jogador *player, int dificuldade);

	// setup
	bool le_fich(string nome_fich);
	void mostra_mapa();
	void mostra_navios();
	
	int pesquisaNavio(int num) const;
	int pesquisaPiratas(int num) const;
	int getSizeNavios() const { return navios.size(); }
	int getSizeNaviosInimigos() const { return naviosInimigos.size(); }
	Navio * getNavio(int i) const;
	Navio * getPirata(int i) const;
	Navio * getNaviobyPos(int p) const;
	Navio * getPiratabyPos(int p) const;
	//get Jogador
	int jog_getmoedas();

	//get Config
	int conf_getpreconavios();
	int precoNavio(char tipo);
	bool canMoveNavio(int x, int y, int qual);
	bool isAgua(int x, int y);
	bool isTerra(int x, int y);
	bool isPortoAmigo(int x, int y);
	bool isOcupado(int x, int y);
	bool moveNavio(int id, string key);
	bool compraNavio(char tipo);
	bool vendeNavio(int id);
	bool vendeMercadoria(int id);
	bool compraMercadoria(int id, int num);
	bool compraSoldados(int id, int num);
	void adicionaMoedas(int num);
	void removeMoedas(int num);
	bool acrescentaNavioPirata(int x, int y, char tipo);
	Porto * portoPrincipal();
	int getNavInimId(int i);
	int getNavInimX(int i);
	int getNavInimY(int i);
	int getNavX(int i);
	int getNavY(int i);
	int getNavId(int i);
	int getxEvento() const;
	Evento * getEvento() const;
	int getDificuldade() { return dificuldade; }
	int pontuacao();
	string getPlayer() const { return jogador->getNome(); }
	coords semFronteiras(int x, int y);
	int procuraInimigos(int t, int i);
	int procuraAmigos(int t, int i);
	int procuraInimigosDeriva(int t, int i);
	int procuraAmigosDeriva(int t, int i);
	bool batalha(int i, int j);
	void procuraBatalhas();
	void resetMoveu();
	float hipotenusa(coords a, coords b);
	bool vaiparacoords(int id, int x, int y);
	bool vaiparaporto(int id, char c);
	coords procuraPorto(char c);
	bool isDestino(int x, int y, coords destino);
	void bebeAgua();
	bool hasPeixe(int x, int y);
	bool hasNavio(int x, int y);
	coords maisPerto(coords atual, int x, int y, int cel);
	void spawnPeixes();
	void navioSemDono();
	void spawnInimigos();
	void inimigoTransfereSoldados(int ind1, int ind2);
	void amigoTransfereAgua(int ind1, int ind2);
	void amigoTransfereSoldados(int ind1, int ind2);
	void procuraBatalhasPorto();
	int procuraPortoInimigo(int t, int i);
	int procuraPortoAmigo(int t, int i);
	bool batalhaPorto(int i, int p);
	bool batalhaPortoPirata(int i, int p);
	void trocaPorto(int m);
	void processaPesca();
	void trocaAgua(int a, int s);
	void reporAgua();
	// debug
	void mostraNavios() const;
	void mostraPortos() const;
	void mostraNaviosInimigos() const;
	void criaEventoCoords(char tipo, int x, int y);
	void criaEventoNav(char tipo, int id);
	void processaEventos();
	int getPrecoCompraMercadoria() const { return config.precocompmercad; }
	int getPrecoVendaMercadoria() const { return config.precovendmercad; }
	int getPrecoSoldados() const { return config.precosoldado; }
	int getPrecoPeixe() const { return config.precovendpeixe; }
	char mapa_getTipo(int i);
	void evento_tempestade(int x, int y);
	void evento_sereias(int id);
	void evento_calmaria(int x, int y);
	coords gera2x2();
	coords geraCoordsDestino(int id);
	coords geraCoordsDestinoPirata(int id);
	Navio* evento_motim(bool & first, int id);
	void eliminaDestrocos();
	bool afetado(int i);
	void checkEvento();
	vector<string> devolveLog();
	void trataLog();
	void updateLog(string s);
	void movimentoAuto(vector <string> & ordens);
	void escunaAutoFull(int i, vector <string> &ordens);
	void escunaAuto(int i, vector <string> &ordens);
	int procuraPeixe(int t, int i);
	void trocaPeixe(int b, int e);
	bool moveDeriva(int t, int pos);
	Jogo & operator=(const Jogo & ob);
	void limpaDados();
	void saveGame(string nome);
	bool loadGame(string nome);
	bool delGame(const char *nome);
	~Jogo();
};

int geraNumero(int x);


#endif
