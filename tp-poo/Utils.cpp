#include "pch.h"
#include "Utils.h"

int Utils::menu_opt(string s)
{
	auto opt = -1;

	if (s == "exec")
	{
		opt = 1;
	}
	else if (s == "prox")
	{
		opt = 2;
	}
	else if (s == "compranav")
	{
		opt = 3;
	}
	else if (s == "vendenav")
	{
		opt = 4;
	}
	else if (s == "lista")
	{
		opt = 5;
	}
	else if (s == "compra")
	{
		opt = 6;
	}
	else if (s == "vende")
	{
		opt = 7;
	}
	else if (s == "move")
	{
		opt = 8;
	}
	else if (s == "auto")
	{
		opt = 9;
	}
	else if (s == "stop")
	{
		opt = 10;
	}
	else if (s == "pirata")
	{
		opt = 11;
	}
	else if (s == "evpos")
	{
		opt = 12;
	}
	else if (s == "evnav")
	{
		opt = 13;
	}
	else if (s == "moedas")
	{
		opt = 14;
	}
	else if (s == "vaipara") // atencao que existem dois
	{
		opt = 15;
	}
	else if (s == "vaiparav2")
	{
		opt = 16;
	}
	else if (s == "comprasold")
	{
		opt = 17;
	}
	else if (s == "saveg")
	{
		opt = 18;
	}
	else if (s == "loadg")
	{
		opt = 19;
	}
	else if (s == "delg")
	{
		opt = 20;
	}
	else if (s == "sair")
	{
		opt = 0;
	}
	else if (s == "help")
		opt = 21;
	else if (s.empty())
		opt = -2;

	return opt;
}

int Utils::opt(int opt, istringstream &iss, Jogo &jg)
{
	switch (opt)
	{
		Navio* ver;
	case 2: // prox
		int id;
		iss >> id;
		ver = jogador.encontraNav(id);
		if (ver == nullptr)
		{
			cout << "O barco com id [" << id << "] nao existe ..." << endl;
		}
		else
		{
			jogador.moveNavio(id, mapa, cfg);
		}
		break;

	case 3: // compranav <T>

		char tipo;
		iss >> tipo;

		// garantir que nao ha erros
		if (jg.jog_getmoedas() >= jg.conf_getpreconavios()){
			if (jg.compra_navio(toupper(tipo))) {
				cout << "Navio comprado com sucesso!" << '\n' << "Moedas: " << jg.jog_getmoedas() << endl;
			}
			else{
				cout << "[ERRO] Tipo: " << "<" << tipo << "> nao existe \n" << "COMANDO : compranav <V/G/E/F/R> " << endl;
			}
		
		}
		else
			cout << "Moedas insuficientes...\n" << "O jogador tem " << jg.jog_getmoedas() << " moedas e sao precisas " << jg.conf_getpreconavios() << " moedas" << endl;

		//switch (tipo)
		//{
		//case 'V': // veleiro
		//	Jogador.compraVeleiro();

		//	/*if (jogador.getMoedas() >= cfg.preconavio) {

		//		auto* x = new Navio(tipo, cfg.preconavio, 200, 0, 40, jogador.getPrin_x(), jogador.getPrin_y());
		//		jogador.pagar(cfg.preconavio);
		//		jogador.addNavio(x);
		//		cout << "Moedas: " << jogador.getMoedas() << endl;
		//	}
		//	else
		//		cout << "Moedas insuficientes...\n" << "O jogador tem " << jogador.getMoedas() << " moedas e sao precisas " << cfg.preconavio << " moedas" << endl;
		//	break;*/

		//case 'G': // galeao
		//	if (jogador.getMoedas() >= cfg.preconavio)
		//	{
		//		auto* x = new Navio(tipo, cfg.preconavio, 400, 0, 70, jogador.getPrin_x(), jogador.getPrin_y());
		//		jogador.pagar(cfg.preconavio);
		//		jogador.addNavio(x);
		//		cout << "Moedas: " << jogador.getMoedas() << endl;
		//	}
		//	else
		//		cout << "Moedas insuficientes...\n" << "O jogador tem " << jogador.getMoedas() << " moedas e sao precisas " << cfg.preconavio << " moedas" << endl;
		//	break;

		//case 'E': // escuna
		//	if (jogador.getMoedas() >= cfg.preconavio)
		//	{
		//		auto* x = new Navio(tipo, cfg.preconavio, 100, 0, 20, jogador.getPrin_x(), jogador.getPrin_y());
		//		jogador.pagar(cfg.preconavio);
		//		jogador.addNavio(x);
		//		cout << "Moedas: " << jogador.getMoedas() << endl;
		//	}
		//	else
		//		cout << "Moedas insuficientes...\n" << "O jogador tem " << jogador.getMoedas() << " moedas e sao precisas " << cfg.preconavio << " moedas" << endl;
		//	break;

		//case 'F': // fragata
		//	if (jogador.getMoedas() >= cfg.preconavio)
		//	{
		//		auto* x = new Navio(tipo, cfg.preconavio, 500, 0, 0, jogador.getPrin_x(), jogador.getPrin_y());
		//		jogador.pagar(cfg.preconavio);
		//		jogador.addNavio(x);
		//		cout << "Moedas: " << jogador.getMoedas() << endl;
		//	}
		//	else
		//		cout << "Moedas insuficientes...\n" << "O jogador tem " << jogador.getMoedas() << " moedas e sao precisas " << cfg.preconavio << " moedas" << endl;
		//	break;

		//case 'R': // especial
		//	cout << "Especial" << endl;
		//	break;

		//default:
		//	cout << "[ERRO] Tipo: " << "<" << tipo << "> nao existe \n" << "COMANDO : compranav <V/G/E/F/R> " << endl;
		//	break;
		//}
		//break;

	case 4: // vendenav <T>
		cout << "Navio vendido!" << endl;
		break;
	case 5: // lista
		cout << "lista!" << endl;
		break;
	case 6: // compra <N> <M>
		cout << "compra!" << endl;
		break;
	case 7: // vende <N>
		cout << "vende !" << endl;
		break;
	case 8: // move <N> <X>
		cout << "move!" << endl;
		break;
	case 9: // auto <N>
		cout << "auto!" << endl;
		break;
	case 10: // stop <N>
		cout << "stop!" << endl;
		break;
	case 11: // pirata <x> <y> <T>
		cout << "pirata!" << endl;
		break;
	case 12: // evpos <E> <x> <y>
		cout << "evpos!" << endl;
		break;
	case 13: // evnav <E> <N>
		cout << "evnav" << endl;
		break;
	case 14: // moedas <N>
		cout << "moedas" << endl;
		break;
	case 15: // vaipara <N> <x> <y>
		cout << "vaipara" << endl;
		break;
	case 16: // vaipara 2 <N> <P>
		cout << "vaipara_v2" << endl;
		break;
	case 17: // comprasold <N> <S>
		cout << "comprasold" << endl;
		break;
	case 18: // saveg <nome>
		cout << "saveg" << endl;
		break;
	case 19: // loadg <nome>
		cout << "loadg" << endl;
		break;
	case 20: // delg <nome>
		cout << "delg" << endl;
		break;
	case 21: // help
		cout << "Comando: " << endl;
		cout << " > exec <nomeFicheiro>" << "\toperacional" << endl;
		cout << " > prox" << "\toperacional" << endl;
		cout << " > compranav <T>" << "\toperacional" << endl;
		Consola::setTextColor(8);
		cout << " > lista" << endl;
		cout << " > vendenav <N>" << endl;
		cout << " > lista" << endl;
		cout << " > vende" << endl;
		cout << " > move <N> <X>" << endl;
		cout << " > auto <N>" << endl;
		cout << " > stop <N>" << endl;
		cout << " > pirata <x> <y> <t>" << endl;
		cout << " > evpos <E> <x> <y>" << endl;
		cout << " > evnav <E> <N>" << endl;
		cout << " > moedas <N>" << " [DEBUG]" << endl;
		cout << " > vaipara <N> <x> <y>" << endl;
		cout << " > vaipara <N> <P>" << endl;
		cout << " > comprasold <N> <S>" << endl;
		cout << " > saveg <nome>" << endl;
		cout << " > loadg <nome>" << endl;
		cout << " > delg <nome>" << endl;
		Consola::setTextColor(7);
		cout << " > sair" << endl;
		break;
	case 0: // sair
		cout << "SHUTING DOWN!" << endl;
		break;
	default:
		break;
	}
	return opt;
}
