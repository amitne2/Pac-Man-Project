#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "Point.h"

class ThePacmanGame;

class Game_Object {
protected:
	Point position[2];
	Point originalPosition;
	int direction;
	ThePacmanGame* theGame;
public:
	Game_Object();
	void setGame(ThePacmanGame* _theGame);
	void resetOriginalPosition();
	void setOriginalPosition(int _x, int _y);
	Point getCurrentPosition();
	void setDirection(int _direction);
	int getDirection();
	//void move(const Point p);
	~Game_Object() {}
};


#endif