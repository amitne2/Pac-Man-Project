#include "Point.h"

Point::Point(int _x, int _y) : x{ _x }, y{ _y }{};

void Point::draw(int num, char ch) const {
	gotoxy(x, y);
	if (num == DRAW_CHARACTER)
		cout << ch;
	else
		cout << num;
	cout.flush();
}

//void Point::draw(int points) const {
//	gotoxy(x, y);
//	cout << ch;
//	cout.flush();
//}

void Point::move(int direction, int object)
	{
		switch (direction) {
		case 0: // UP
			--y;
			if (y < 0 && object) {
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
			if (x < 0 && object) {
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
