 
#include "Config.h"

void var(string var, istringstream &le, Config& cfg)
{
	int value;
	if (var == "moedas") {
		le >> value;
		cfg.moedas = value;
	}
	else if (var == "probpirata") {
		le >> value;
		cfg.probpirata = value;
	}
	else if (var == "preconavio") {
		le >> value;
		cfg.preconavio = value;
	}
	else if (var == "precosoldado") {
		le >> value;
		cfg.precosoldado = value;
	}
	else if (var == "precovendpeixe") {
		le >> value;
		cfg.precovendpeixe = value;
	}
	else if (var == "precocompmercad") {
		le >> value;
		cfg.precocompmercad = value;
	}
	else if (var == "precovendmercad") {
		le >> value;
		cfg.precovendmercad = value;
	}
	else if (var == "soldadosporto") {
		le >> value;
		cfg.soldadosporto = value;
	}
	else if (var == "probevento") {
		le >> value;
		cfg.probevento = value;
	}
	else if (var == "probtempestade") {
		le >> value;
		cfg.probtempestade = value;
	}
	else if (var == "probsereias") {
		le >> value;
		cfg.probsereias = value;
	}
	else if (var == "probcalmaria") {
		le >> value;
		cfg.probcalmaria = value;
	}
	else if (var == "probmotim") {
		le >> value;
		cfg.probmotim = value;
	}
	else if (var == "precoveleiro") {
		le >> value;
		cfg.precoveleiro = value;
	}
	else if (var == "precogaleao") {
		le >> value;
		cfg.precogaleao = value;
	}
	else if (var == "precoescuna") {
		le >> value;
		cfg.precoescuna = value;
	}
	else if (var == "precofragata") {
		le >> value;
		cfg.precofragata = value;
	}
	else if (var == "precoespecial") {
		le >> value;
		cfg.precoespecial = value;
	}		
}


