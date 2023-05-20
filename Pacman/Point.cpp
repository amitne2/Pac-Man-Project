#include "Point.h"
#include "ThePacmanGame.h"
#include <cmath>

using std::cout;
using std::cin;
using std::endl;

//Constructor Point
Point::Point(int _x, int _y) : x{ _x }, y{ _y }{};

//Get x parameter of point
int Point::getX() const {
	return x;
}

//Get y parameter of point
int Point::getY() const {
	return y;
}

//Set x,y parameters of point
void Point::set(int _x, int _y) {
	x = _x;
	y = _y;
}

//Draw a character ot a number (according to the parameters that re sent) in point location
void Point::draw(int num, char ch) const {
	gotoxy(x, y);
	if (num == DRAW_CHARACTER)
		cout << ch;
	else
		cout << num;
	cout.flush();
}

//Set x or y parameter according to the direction sent in the function. 
//The object is sent to identify if it is pacman or ghost.
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
				x = 0;
			}
			break;
		case 4:
			break; // DO NOTHING, STAY PUT
		}
	}

//Check next move of the object (does not move the object!)
Point Point::next(int direction, int object) {
	Point next = *this;
	next.move(direction, object);
	return next;
}


int Point::getDistance(Point p)
{
	return(sqrt(pow(x - p.x,2) + pow(y - p.y,2)));
}