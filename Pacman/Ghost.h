#ifndef _GHOST_H_
#define _GHOST_H_

#include <cstring>
#include "Point.h"

#define GHOST_SYMBOL char(234)

class ThePacmanGame;

class Ghost {
private:
	Point position[2];
	int direction; // = rand() % 3;
	Point originalPosition;
	//char arrowKeys[5];
	//int points = 0;
	ThePacmanGame* theGame;

public:
	Ghost(int _x, int _y);

	void setGame(ThePacmanGame* _theGame);

	void setOriginalPosition();
	Point getCurrentPosition();
	//int getDirection(char key);
	//void setDirection();
	//void setDirection(int dir);
	void move(const Point p);
};

#endif
