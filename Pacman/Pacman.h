#ifndef _PACMAN_H_
#define _PACMAN_H_

#include <cstring>
#include "Point.h"

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
	Pacman();
	Pacman(int y, int x);
	void setGame(ThePacmanGame* _theGame) {
		theGame = _theGame;
	}
	void setOriginalPosition();
	void setLives();
	void setDirection(int dir);
	int getLives();
	int getDirection(char key);
	Point getPosition();
	void move();
	//void ghostAtePacman();
};

#endif