#include "Point.h"
#include "ThePacmanGame.h"

class Pacman {
private:
	Point position;
	int direction = 3;
	char arrowKeys[5];
	ThePacmanGame* theGame;

public:

	void setGame(ThePacmanGame* _theGame) {
		theGame = _theGame;
	}
	void setPosition(int y, int x)
	{
		position.set(x, y);
	}

	void setArrowKeys(const char* keys)
	{
		arrowKeys[0] = keys[0]; // UP
		arrowKeys[1] = keys[1]; // DOWN
		arrowKeys[2] = keys[2]; // LEFT
		arrowKeys[3] = keys[3]; // RIGHT
		arrowKeys[4] = keys[4]; // STAY
	}

	int getDirection(char key)
	{
		for (int i = 0; i < 5; i++)
		{
			if (key == arrowKeys[i])
				return i;
		}
		return -1;
	}
	void setDirection(int dir) {
		direction = dir;
	}

	void move()
	{
		position.move(direction);
		//setTextColor(color);
		position.draw('@');
	}
};