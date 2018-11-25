#include "Porto.h"
#include <iostream>

using namespace std;

Porto::Porto(char ch, int a, int b)
	:id(ch), x(a), y(b)
{
//	cout << "ID: " << ch << "\nCoords: (" << x << ";" << y << ")" << endl;
}

char Porto::getID() const {
	return id;
}

int Porto::get_x() const {
	return x;
}

int Porto::get_y() const {
	return y;
}

Porto::~Porto()
{
}
