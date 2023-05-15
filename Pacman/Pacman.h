#ifndef _PACMAN_H_
#define _PACMAN_H_

#include <cstring>
#include "Game_Object.h"
//#include "ThePacmanGame.h"
#define PACMAN_SYMBOL char(2)

//class ThePacmanGame;

class Pacman : public Game_Object {
private:
	int lives;
	int points;
	char arrowKeys[5];
	void setArrowKeys(const char* keys);

public:
	Pacman();
	void setLives();
	int getPoints();
	void setPoints(int _points);
	int getLives();
	int getDirection(char key);
	void move();
	~Pacman();
};

#endif