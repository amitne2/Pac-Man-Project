#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
#include "io_utils.h" 

using namespace std;

class Point {
	int x = 1, y = 1;
public:
	int getX() const {
		return x;
	}
	int getY() const {
		return y;
	}
	void set(int _x, int _y) {
		x = _x;
		y = _y;
	}
	void draw(char ch) {
		gotoxy(x, y);
		cout << ch;
		cout.flush();
	}
	//void move();
	void move(int direction, int object);
	
	Point next(int direction, int object) {
		Point next = *this;
		next.move(direction, object);
		return next;
	}
	//bool checkIfTheSamePosition(const Point& p1, const Point &p2);
};

#endif