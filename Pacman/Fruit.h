#ifndef _FRUIT_H_
#define _FRUIT_H_

#include "Game_Object.h"
#include <vector>

class Ghost;

class Fruit : public Game_Object {
private:
	char fruitSymbol;
	bool fruitOnBoard;
	int displayCounter;
public:
	Fruit(int _x=0, int _y=0, int _direction=3, char _fruitSymbol='5');
	void setFruitPosition(const Point& pac, const std::vector<Ghost>& ghosts);
	bool getFruitOnBoard();
	void setFruitOnBoard(bool set);
	void setDisplayCounter();
	void setFruitSymbol();
	char getFruitSymbol() const;
	void move(const Point& pac, std::vector<Ghost>& ghosts);
	void turnOffFruit();
	~Fruit() {} //distructor
};

#endif