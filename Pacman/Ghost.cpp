#include "Ghost.h"
#include "ThePacmanGame.h"


void Ghost::setPosition(int y, int x)
{
	position[0].set(x, y);
	position[1].set(x, y);
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
		
	position[1].draw('.');
	position[0].draw('$');
}
