#include "Point.h"

void Point::move() {
		int dir = rand() % 4;
		move(dir);
	}

void Point::move(int direction)
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
		case 4:
			break; // DO NOTHING, STAY PUT
		}
	}
