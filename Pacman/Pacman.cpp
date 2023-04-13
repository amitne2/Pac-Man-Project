#include "Pacman.h"
#include "ThePacmanGame.h"
//pacmannnnnnnnnn

void Pacman::setPosition(int y, int x)
{
	position[0].set(x, y);
	position[1].set(x,y);
}


int Pacman::getDirection(char key)
{
	for (int i = 0; i < 5; i++)
	{
		if (key == arrowKeys[i])
			return i;
	}
	return -1;
}
void Pacman::setDirection(int dir)
{
	direction = dir;
}

void Pacman::move()
{
	//char c = theGame->getBoardSignInPosition(position[0]);
	position[1] = position[0];
	position[0].move(direction);
	
	if (theGame->isWall(position[1].next(direction)))
	{
		direction = 4; // pacman stops at wall
		//theGame->drawOnBoard(position[1], '+');
		position[0] = position[1];
		position[1] = position[0];
	}
	else
	{
		//position[0].move(direction, c);
		//setTextColor(color);
		if (direction != 4) // STAY POSITION
			position[1].draw(' ');
		position[0].draw('@');
	}
}
