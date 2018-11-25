#ifndef __PORTO__
#define __PORTO__

class Porto {
	char id;
	int x;
	int y;
public:
	Porto(char id, int x, int y);
	~Porto();
	char getID() const;
	int get_x() const;
	int get_y() const;
};

#endif