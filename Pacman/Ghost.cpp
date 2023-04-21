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

Point Ghost::getCurrentPosition()
{
	return position[0];
}


void Ghost::move(const Point p)
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


	if (theGame->checkIfTheSamePosition(p, position[0]))
	{
		theGame->setBoardBeforeStrike(position[1]);
		if(theGame->getColored())
			setTextColor(LIGHTBLUE);
		position[0].draw(DRAW_CHARACTER, GHOST_SYMBOL);
		Sleep(2000);
		setTextColor(WHITE);
		theGame->ghostAtePacman();
	}

	else
	{
		theGame->setBoardBeforeStrike(position[1]);
		if(theGame->getColored())
			setTextColor(LIGHTBLUE);
		position[0].draw(DRAW_CHARACTER, GHOST_SYMBOL);
		position[1] = position[0];
		setTextColor(WHITE);
	}
}
