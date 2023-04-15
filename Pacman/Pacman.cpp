#include "Pacman.h"
#include "ThePacmanGame.h"

Pacman:: Pacman(int y, int x)
{
	originalPosition.set(x, y);
	position[0] = position[1] = originalPosition;
	lives = 2;
	direction = 3;
	points = 0;
	setArrowKeys("wxads");
}

void Pacman::setOriginalPosition()
{
	position[0] = position[1] = originalPosition;
}

void Pacman::setArrowKeys(const char* keys)
{
	arrowKeys[0] = keys[0]; // UP
	arrowKeys[1] = keys[1]; // DOWN
	arrowKeys[2] = keys[2]; // LEFT
	arrowKeys[3] = keys[3]; // RIGHT
	arrowKeys[4] = keys[4]; // STAY
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


void Pacman::setLives()
{
	lives--;
}

int Pacman::getLives()
{
	return lives;
}

Point Pacman::getPosition()
{
	return position[0];
}

void Pacman::move()
{
	position[1] = position[0];
	position[0].move(direction, PACMAN);
	
	if (theGame->isWall(position[1].next(direction, PACMAN), PACMAN))
	{
		direction = 4; // pacman stops at wall
		position[0] = position[1];
		position[1] = position[0];
	}

	else if (theGame->isGhost())
		theGame->ghostAtePacman();

	else
	{
		if (theGame->isBreadCrumbs(position[1].next(direction, PACMAN)))
		{
			points++;
			theGame->updateBoard(position[1]);
		}

		//setTextColor(color);
		if (direction != 4) // STAY POSITION
			position[1].draw(' ');
		position[0].draw('@');
	}

	//if(points == NUM_OF_FRUITS)
	//check lives & points and update
}
