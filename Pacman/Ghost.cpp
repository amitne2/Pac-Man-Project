#include "Ghost.h"
#include "ThePacmanGame.h"

//Constructor ghost
Ghost::Ghost(int _y, int _x)
{
	originalPosition.set(_x, _y);
	position[0] = position[1] = originalPosition; //set the start position
}

//Set the pacmanGame pointer
void Ghost:: setGame(ThePacmanGame* _theGame)
{
	theGame = _theGame;
}

//Set ghost original position 
void Ghost::setOriginalPosition()
{
	position[0] = position[1] = originalPosition;
}
//this Function return the postion of the ghost
Point Ghost::getCurrentPosition()
{
	return position[0];
}
//This function ramdon a number between 1-4 for direction
//Checks the next move is valid (not wall) - If it's a wall, random number until it doesn't
//Checks if the ghost is on pacman position (strike in the game) - update the relevant variables
void Ghost::move(const Point p)
{
	int dir;
	dir = rand() % 3; //random a number 
	position[1] = position[0]; 
	position[0].move(dir, GHOST);
	
	while (theGame->isWall(position[1].next(dir, GHOST), GHOST)) //Checks if the next move position is a wall
	{
		position[0] = position[1];
		dir = rand() % 3;
		position[1] = position[0];
		position[0].move(dir, GHOST);
	}
	theGame->setBoardBeforeStrike(position[1]); //Update board before strike

	if (theGame->checkIfTheSamePosition(p, position[0])) //Checks if the next move is on pacman position
	{
		if(theGame->getColored()) //Set color
			setTextColor(LIGHTMAGENTA);
		position[0].draw(DRAW_CHARACTER, GHOST_SYMBOL);
		Sleep(2000);
		setTextColor(WHITE); 
		theGame->ghostAtePacman();
	}

	else
	{
		if(theGame->getColored()) //Set color
			setTextColor(LIGHTMAGENTA);
		position[0].draw(DRAW_CHARACTER, GHOST_SYMBOL); //Draw new position
		position[1] = position[0];
		setTextColor(WHITE);
	}
}

//Empty destructor 
Ghost::~Ghost() {}

