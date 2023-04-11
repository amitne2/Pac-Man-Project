#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

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
	void move() {
		int dir = rand() % 4;
		move(dir);
	}
	void move(int direction)
	{
		switch (direction) {
		case 0: // UP
			--y;
			if (y < 1) {
				y = 24;
			}
			break;
		case 1: // DOWN
			++y;
			if (y > 24) {
				y = 1;
			}
			break;
		case 2: // LEFT
			--x;
			if (x < 1) {
				x = 79;
			}
			break;
		case 3: // RIGHT
			++x;
			if (x > 79) {
				x = 1;
			}
			break;
		}
	}
	Point next(int direction) {
		Point next = *this;
		next.move(direction);
		return next;
	}
};

#endif