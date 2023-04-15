#include "Ghost.h"
#include "ThePacmanGame.h"

Ghost::Ghost(int _y, int _x)
{
	originalPosition.set(_x, _y);
	position[0] = position[1] = originalPosition;
}

void Ghost:: setGame(ThePacmanGame* _theGame)
{
	theGame = _theGame;
}

void Ghost::setOriginalPosition()
{
	position[0] = position[1] = originalPosition;
}

Point Ghost::getPosition()
{
	return position[0];
}

void Ghost::move()
{
	int dir;
	
	dir = rand() % 3;
	position[1] = position[0];
	position[0].move(dir, GHOST);
	
	while (theGame->isWall(position[1].next(dir, GHOST), GHOST))
	{
		position[0] = position[1];
		dir = rand() % 3;
		position[1] = position[0];
		position[0].move(dir, GHOST);
	}
	
	//else if() //ghost

	
	/*if (theGame->isFruit(position[1].next(direction)))
			points++;*/

	//setTextColor(color);
	if (theGame->isBreadCrumbs(position[1]))
		position[1].draw('.');
	else
		position[1].draw(' ');
	position[0].draw('$');
}
