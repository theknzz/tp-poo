#include "Porto.h"
#include "Config.h"

#include <sstream>
#include <iostream>

char Porto::conta = 'a';

using namespace std;

Porto::Porto(char ch, int a, int b)
	:x(a), y(b) {
	if (ch == '?'){
		id = conta++;
	}
	else{
		id = ch;
	}
}

char Porto::getID() const {
	return id;
}

void Porto::setID(char c) {
	id = c;
}

int Porto::get_x() const {
	return x;
}

int Porto::get_y() const {
	return y;
}

string Porto::getAsString() {
	ostringstream oss;
	oss << "Porto: " << getID() << "\nCoords: {" << get_x() << "," << get_y() << "}" << endl;
	return oss.str();
}

Porto * Porto::duplica() const {
	return new Porto(*this);
}

Porto::~Porto()
{
}

