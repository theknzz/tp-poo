#pragma once
#include <string>
#include "Jogo.h"
#include "consola.h"

class Utils
{
public:
	// menu
	static int menu_opt(string s);
	static int opt(int opt, istringstream &iss, Jogo &jg);
};
