#include "Fruit.h"
#include "ThePacmanGame.h"

Fruit::Fruit(int _x, int _y, int _direction) : Game_Object(_x, _y, _direction)
{
	creature = '0' + (5 + rand() % 5);
	displayCounter = 0;
	fruitOnBoard = false;
}

void Fruit::setFruitPosition(const Point& pac, const Point& ghost)
{
	Point temp;
	bool valid = false;
	while (!valid)
	{
		temp.set(rand() % 24, rand() % 80);
		if (!theGame->isWall(position[1], NOT_PACMAN) && !theGame->checkIfTheSamePosition(temp, pac) && !theGame->checkIfTheSamePosition(temp, ghost))
			valid = true;
	}
	fruitOnBoard = true;
	this->position[0] = this->position[1] = temp;
}

bool Fruit::getFruitOnBoard()
{
	return fruitOnBoard;
}

void Fruit::setFruitOnBoard(bool set)
{
	fruitOnBoard = set;
}

void Fruit::setDisplayCounter()
{
	displayCounter = 5 + rand() % 26;
}

//This function random a number between 1-4 for direction
//Checks the next move is valid (not wall) - If it's a wall, random number until it doesn't
//Checks if the fruit is on pacman or ghost position, if pacman - update the relevant variables
void Fruit::move(const Point& pac, const Point& ghost)
{
	direction = rand() % 3; //random a number 
	position[1] = position[0];
	position[0].move(direction, NOT_PACMAN);

	while (theGame->isWall(position[1].next(direction, NOT_PACMAN), NOT_PACMAN)) //Checks if the next move position is a wall
	{
		position[0] = position[1];
		direction = rand() % 3;
		position[0].move(direction, NOT_PACMAN);
	}

	theGame->setBoardBeforeObjectMoves(position[1]); //Update board before move

	if (fruitOnBoard)
	{
		if (theGame->checkIfTheSamePosition(ghost, position[0])) //Checks if the next move is on ghost position
		{
			if (theGame->getColored()) //Set color
				setTextColor(LIGHTMAGENTA);
			position[0].draw(DRAW_CHARACTER, GHOST_SYMBOL);
			fruitOnBoard = false;
			displayCounter = 0;
			setTextColor(WHITE);
		}

		else if (theGame->checkIfTheSamePosition(pac, position[0])) //Checks if the next move is on pacman position
		{
			if (theGame->getColored()) //Set color
				setTextColor(LIGHTYELLOW);
			position[0].draw(DRAW_CHARACTER, PACMAN_SYMBOL);
			fruitOnBoard = false;
			displayCounter = 0;
			setTextColor(WHITE);
			theGame->pacmanAteFruit(creature - '0');
		}

		else
		{
			if (theGame->getColored()) //Set color
				setTextColor(LIGHTMAGENTA);
			position[0].draw(DRAW_CHARACTER, creature); //Draw new position
			position[1] = position[0];
			setTextColor(WHITE);
		}
	}
	/////check with sarel abolut fruit meeting another fruit
}

