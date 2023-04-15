#include "Point.h"

///*void Point::move() {
//		int dir = rand() % 4;
//		move(dir, 0);
//	*/}

Point::Point(int _x, int _y) : x{ _x }, y{ _y }{};

void Point::draw(int points)
{
	gotoxy(x, y);
	cout << points;
	cout.flush();
}

void Point::move(int direction, int object)
	{
		switch (direction) {
		case 0: // UP
			--y;
			if (y < 1 && object) { //pacman is 1, if pacman
				y = 23;
			}
			break;
		case 1: // DOWN
			++y;
			if (y > 24 && object) {
				y = 1;
			}
			break;
		case 2: // LEFT
			--x;
			if (x < 1 && object) {
				x = 79;
			}
			break;
		case 3: // RIGHT
			++x;
			if (x > 79 && object) {
				x = 1;
			}
			break;
		case 4:
			break; // DO NOTHING, STAY PUT
		}
	}
