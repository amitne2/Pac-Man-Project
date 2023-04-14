#ifndef _PACMAN_H_
#define _PACMAN_H_

#include <cstring>
#include "Point.h"

class ThePacmanGame;

class Pacman {
private:
	Point position[2];
	int direction = 3;
	char arrowKeys[5];
	int points = 0;
	ThePacmanGame* theGame;

public:

	void setGame(ThePacmanGame* _theGame) {
		theGame = _theGame;
	}
	
	void setPosition(int y, int x);

	void setArrowKeys(const char* keys)
	{
		arrowKeys[0] = keys[0]; // UP
		arrowKeys[1] = keys[1]; // DOWN
		arrowKeys[2] = keys[2]; // LEFT
		arrowKeys[3] = keys[3]; // RIGHT
		arrowKeys[4] = keys[4]; // STAY
	}

	int getDirection(char key);
	void setDirection(int dir);
	void move();
};

#endif