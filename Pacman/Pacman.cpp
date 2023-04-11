#include "Point.h"

class Pacman {
private:
	Point position;
	int direction = 3;

	char arrowKeys[5];


public:

	void setArrowKeys(const char* keys)
	{
		arrowKeys[0] = keys[0]; // UP
		//I
		arrowKeys[1] = keys[1]; // DOWN
		arrowKeys[2] = keys[2]; // LEFT
		arrowKeys[3] = keys[3]; // RIGHT
		arrowKeys[4] = keys[4]; // STAY
	}
};