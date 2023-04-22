#ifndef _GHOST_H_
#define _GHOST_H_

#include <cstring>
#include "Point.h"

#define GHOST_SYMBOL char(234)

class ThePacmanGame;

class Ghost {
private:
	Point position[2];
	int direction; 
	Point originalPosition;
	ThePacmanGame* theGame;

public:
	Ghost(int _x, int _y);
	void setGame(ThePacmanGame* _theGame);
	void setOriginalPosition();
	Point getCurrentPosition();
	void move(const Point p);
	~Ghost();
};

#endif
