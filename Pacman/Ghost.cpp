#include "Ghost.h"

//Constructor ghost
Ghost::Ghost(int _y, int _x, int _direction, char _gameLevel, int _countSteps) : Game_Object(_x, _y, _direction) 
{
	gameLevel = _gameLevel;
	countSteps = _countSteps;
}

//This function ramdon a number between 1-4 for direction
//Checks the next move is valid (not wall) - If it's a wall, random number until it doesn't
//Checks if the ghost is on pacman position (strike in the game) - update the relevant variables
void Ghost::move(const Point& pac)
{
	//int dir;
	//dir = rand() % 3; //random a number 
	setDirection(pac);
	position[1] = position[0]; 
	position[0].move(direction, NOT_PACMAN);

	while (theGame->isWall(position[1].next(direction, NOT_PACMAN), NOT_PACMAN)) //Checks if the next move position is a wall
	{
		position[0] = position[1];
		direction = rand() % 3;
		position[0].move(direction, NOT_PACMAN);
	}
	theGame->setBoardBeforeObjectMoves(position[1]); //Update board before strike

	if (theGame->checkIfTheSamePosition(pac, position[0])) //Checks if the next move is on pacman position
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

void Ghost::setDirection(const Point& pac)
{
	switch (gameLevel)
	{
	case 'a': //BEST level
		chasePacman(pac);
		break;
	case 'b': //GOOD level
		if (countSteps == MAX_MOVES)
			direction = rand() % 3;
		else
		{
			if (countSteps == MAX_MOVES + 5)
				countSteps = 0;
			chasePacman(pac);
		}
		break;
	case 'c': //NOVICE level
		if (countSteps == MAX_MOVES)
		{
			direction = rand() % 3;
			countSteps = 0;
		}
		break;
	}
}

void Ghost::chasePacman(const Point& pac)
{
	int xGap, yGap;

	if (pac.getY() == position[0].getY()) //same y
	{
		if (pac.getX() > position[0].getX())
			direction = MOVE_UP;
		else if (pac.getX() < position[0].getX())
			direction = MOVE_DOWN;
	}

	else if (pac.getX() == position[0].getX()) //same x
	{
		if (pac.getY() > position[0].getY())
			direction = MOVE_RIGHT;
		else if (pac.getY() < position[0].getY())
			direction = MOVE_LEFT;
	}

	else
	{
		xGap = pac.getX() - position[0].getX();
		yGap = pac.getY() - position[0].getY();

		if (abs(xGap) > abs(yGap))
		{
			if (xGap > 0)
				direction = MOVE_DOWN;
			else
				direction = MOVE_UP;
		}

		else
		{
			if (yGap > 0)
				direction = MOVE_RIGHT;
			else
				direction = MOVE_LEFT;
		}
	}
}

//Empty destructor 
Ghost::~Ghost() {}

