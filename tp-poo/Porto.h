#ifndef __PORTO__
#define __PORTO__


#include <string>

using namespace std;

class Porto {
	char id;
	int x;
	int y; 
protected:
	static char conta; // criador do id
public:
	Porto(char id, int x, int y);
	virtual ~Porto();
	char getID() const;
	void setID(char c);
	int get_x() const;
	int get_y() const;
	string getAsString();
	Porto * duplica() const;
};

#endif