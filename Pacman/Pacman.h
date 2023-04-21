#ifndef _PACMAN_H_
#define _PACMAN_H_

#include <cstring>
#include "Point.h"


#define PACMAN_SYMBOL char(2)

class ThePacmanGame;

class Pacman {
private:
	Point position[2];
	Point originalPosition;
	int lives;
	int direction;
	int points;
	char arrowKeys[5];
	ThePacmanGame* theGame;
	void setArrowKeys(const char* keys);

public:
	Pacman(int y, int x);
	void setGame(ThePacmanGame* _theGame) {
		theGame = _theGame;
	}
	void setOriginalPosition();
	void setLives();
	int getPoints();
	void setDirection(int dir);
	int getLives();
	int getDirection(char key);
	Point getCurrentPosition();
	void move();
};

#endif