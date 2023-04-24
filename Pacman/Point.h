#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
#include "io_utils.h" 
#define DRAW_CHARACTER -1

using std::cout;
using std::cin;
using std::endl;

class Point {
	int x, y;
public:
	Point(int x = 1, int y = 1);
	int getX() const;
	int getY() const;
	void set(int _x, int _y);
	void draw(int num, char ch) const;
	void move(int direction, int object);
	Point next(int direction, int object);
	~Point() {} //Distructor
};

#endif