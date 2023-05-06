#ifndef _FRUIT_H_
#define _FRUIT_H_

#include "Game_Object.h"

class Fruit : public Game_Object {
private:
	char creature;
	bool fruitOnBoard;
	int displayCounter;
public:
	Fruit(int _x=0, int _y=0, int _direction=3);
	void setFruitPosition(const Point& pac, const Point& ghost);
	bool getFruitOnBoard();
	void move(const Point& pac, const Point& ghost);
	~Fruit() {}
};

#endif