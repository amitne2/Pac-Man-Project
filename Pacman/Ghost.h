#ifndef _GHOST_H_
#define _GHOST_H_

#include <cstring>
#include "Game_Object.h"
#include "Fruit.h"

constexpr char GHOST_SYMBOL = char(234);
constexpr int MAX_MOVES = 20;

class Ghost : public Game_Object {
private:
	//char gameLevel;
	int countSteps;
	bool levelBIndication;
public:
	Ghost();
	Ghost(int _x, int _y);
	void move(const Point& pac, Fruit* fruitsArr);
	void setDirection(const Point& pac);
	void findShortestPath(const Point& destination);
	~Ghost();
};

#endif
