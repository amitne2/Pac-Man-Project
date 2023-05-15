#ifndef _GHOST_H_
#define _GHOST_H_

#include <cstring>
#include "Game_Object.h"
#include "Fruit.h"
//#include "ThePacmanGame.h"

#define GHOST_SYMBOL char(234)
#define MAX_MOVES 20
#define MOVE_UP 0
#define MOVE_DOWN 1
#define MOVE_LEFT 2
#define MOVE_RIGHT 3

class Ghost : public Game_Object {
private:
	char gameLevel;
	int countSteps;
	bool levelBIndication;
public:
	Ghost();
	Ghost(int _x, int _y);
	void move(const Point& pac, Fruit* fruitsArr);
	void setDirection(const Point& pac);
	void setGameLevel(char level);
	void chasePacman(const Point& pac);
	~Ghost();
};

#endif
