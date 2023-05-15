#include "Fruit.h"
#include "ThePacmanGame.h"

Fruit::Fruit(int _y, int _x, int _direction, char _fruitSymbol)
{
	fruitSymbol = _fruitSymbol;
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

void Fruit::setDisplayCounter(int num)
{
	displayCounter = num;
}

void Fruit::setFruitSymbol()
{
	fruitSymbol = '0' + (5 + rand() % 5);
}

char Fruit::getFruitSymbol()
{
	return fruitSymbol;
}

//This function random a number between 1-4 for direction
//Checks the next move is valid (not wall) - If it's a wall, random number until it doesn't
//Checks if the fruit is on pacman or ghost position, if pacman - update the relevant variables
void Fruit::move(const Point& pac, vector<Ghost>& ghosts)
{
	srand(time(NULL));
	direction = rand() % 3; //random a number 
	position[1] = position[0];
	position[0].move(direction, NOT_PACMAN);

	while (theGame->isWall(position[1].next(direction, NOT_PACMAN), NOT_PACMAN)) //Checks if the next move position is a wall
	{
		position[0] = position[1];
		direction = rand() % 3;
		position[0].move(direction, NOT_PACMAN);
	}
	
	if (fruitOnBoard)
	{
		theGame->setBoardBeforeObjectMoves(position[1]); //Update board before move

		for (int i = 0; i < ghosts.size() && fruitOnBoard; i++)
		{
			if (theGame->checkIfTheSamePosition(ghosts[i].getCurrentPosition(), position[0])) //Checks if the next move is on ghost position
			{
				if (theGame->getColored()) //Set color
					setTextColor(LIGHTMAGENTA);
				//position[0].draw(DRAW_CHARACTER, GHOST_SYMBOL);
				fruitOnBoard = false;
				displayCounter = 0;
				setTextColor(WHITE);
			}
		}

		if (theGame->checkIfTheSamePosition(pac, position[0])) //Checks if the next move is on pacman position
		{
			if (theGame->getColored()) //Set color
				setTextColor(LIGHTYELLOW);
			fruitOnBoard = false;
			displayCounter = 0;
			setTextColor(WHITE);
			theGame->pacmanAteFruit(fruitSymbol - '0');
			theGame->updateBoard(position[0]);
		}

		else if(fruitOnBoard)
		{
			if (theGame->getColored()) //Set color
				setTextColor(LIGHTMAGENTA);
			position[0].draw(DRAW_CHARACTER, fruitSymbol); //Draw new position
			position[1] = position[0];
			setTextColor(WHITE);
		}
	}
}

