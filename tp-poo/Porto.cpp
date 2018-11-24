#include "Porto.h"


Porto::Porto(char ch, int a, int b)
	:id(ch), x(a), y(b)
{

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
