#ifndef _GHOST_H_
#define _GHOST_H_

#include <cstring>
#include "Point.h"

class ThePacmanGame;

class Ghost {
private:
	Point position[2];
	int direction; // = rand() % 3;
	//char arrowKeys[5];
	//int points = 0;
	ThePacmanGame* theGame;

public:

	void setGame(ThePacmanGame* _theGame) {
		theGame = _theGame;
	}

	void setPosition(int y, int x);

	//int getDirection(char key);
	//void setDirection();
	//void setDirection(int dir);
	void move();
};

#endif
