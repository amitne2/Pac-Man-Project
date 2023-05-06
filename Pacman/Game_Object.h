#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "Point.h"
//#include "ThePacmanGame.h"

class ThePacmanGame;

class Game_Object {
protected:
	Point position[2];
	Point originalPosition;
	int direction;
	ThePacmanGame* theGame;
public:
	Game_Object(int _x, int _y, int _direction); //for now
	void setGame(ThePacmanGame* _theGame);
	void setOriginalPosition();
	Point getCurrentPosition();
	void setDirection(int _direction);
	int getDirection();
	//void move(const Point p);
	~Game_Object() {}
};


#endif