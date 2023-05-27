#include "Fruit.h"
#include "ThePacmanGame.h"

using std::vector;

//Constructor
Fruit::Fruit(int _y, int _x, int _direction, char _fruitSymbol)
{
	fruitSymbol = _fruitSymbol;
	turnOffFruit();
}

//This function sets the position of a fruit.
//It goes over the board in a loop and finds a suitable and random position for the fruit.
void Fruit::setFruitPosition(const Point& pac, const vector<Ghost>& ghosts)
{
	int ghostCounter = 0;
	Point temp;
	bool valid = false;
	while (valid == false)
	{
		temp.set(rand() % 79, rand() % 23);
		for(int i=0; i<ghosts.size(); i++)
		{
			if(theGame->checkIfTheSamePosition(temp, ghosts[i].getCurrentPosition()) == false)
				ghostCounter++;
		}
		if (theGame->isWall(temp, NOT_PACMAN) == false && theGame->checkIfTheSamePosition(temp, pac) == false && ghostCounter == ghosts.size())
			valid = true;
		ghostCounter = 0;
	}
	fruitOnBoard = true;
	this->position[0] = this->position[1] = temp;
}

//This function returns true if the fruit is on the board, false if it is not
bool Fruit::getFruitOnBoard()
{
	return fruitOnBoard;
}

//This function sets parameter fruitOnBoard - true to turn it on and false to turn it off 
void Fruit::setFruitOnBoard(bool set)
{
	fruitOnBoard = set;
}

//This function sets a andom numbe to displayCounter - it will determine the number of
//steps the fruit will make until it disappears
void Fruit::setDisplayCounter()
{
	displayCounter = 5 + rand() % 20;
}

//This function sets the fruit's symbol which is a number between 5-9.
void Fruit::setFruitSymbol()
{
	fruitSymbol = '0' + (5 + rand() % 5);
}

//This function returns the fruit's symbol as a character.
char Fruit::getFruitSymbol() const
{
	return fruitSymbol;
}

//This function randoms a number between 1-4 for direction
//Checks the next move is valid (not wall) - If it's a wall, random number until it doesn't
//Checks if the fruit is on pacman or ghost position, if pacman - update the relevant variables
//If ghost - fruit will disappear
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
				position[0].draw(DRAW_CHARACTER, GHOST_SYMBOL);
				turnOffFruit();
				setTextColor(WHITE);
			}
		}

		if (theGame->checkIfTheSamePosition(pac, position[0])) //Checks if the next move is on pacman position
		{
			turnOffFruit();
			theGame->pacmanAteFruit(fruitSymbol - '0');
			theGame->updateBoard(position[0]);
			//theGame->subtractBreadcrumbs(); //////////////
		}

		else if(fruitOnBoard)
		{
			if (displayCounter == 0)
			{
				turnOffFruit();
				//theGame->updateBoard(position[0]);
				theGame->setBoardBeforeObjectMoves(position[0]); //////////// fixed?
			}
			else
			{
				if (theGame->getColored()) //Set color
					setTextColor(LIGHTGREEN);
				position[0].draw(DRAW_CHARACTER, fruitSymbol); //Draw new position
				position[1] = position[0];
				setTextColor(WHITE);
				displayCounter--;
			}
		}
	}
}

//This function 'turns off' the fruit, meaning the fruit will not be seen on board until turned on.
void Fruit::turnOffFruit()
{
	fruitOnBoard = false;
	displayCounter = 0;
}
