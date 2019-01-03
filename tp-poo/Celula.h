#ifndef __CELULA__
#define __CELULA__

#include <string>
//#include "Porto.h"

using namespace std;
class Porto;
class Celula
{
	int x, y;
	char tipo;
	Porto* porto;
	int peixe;

public:
	Celula(int a, int b, char t, Porto* p = nullptr)
		:x(a), y(b), tipo(t), porto(p) {
		if (tipo == '.')
			peixe = 1;
		else
			peixe = 0;
	}

	virtual ~Celula();

	char getTipo()const;
	bool isPorto()const;
	int getPeixe() const;
	void setPeixe(int n);
	void addPeixe();
	bool pesca();
	int get_x() const;
	int get_y() const;
	void set_x(int n);
	void set_y(int n);
	void setPorto(Porto * p);
	Porto * getPorto() const;

	void setTipo(char c);
};

#endif
