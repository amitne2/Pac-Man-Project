#include "Ghost.h"
#include "ThePacmanGame.h"
#include "Fruit.h"
#include <random>

//Constructor ghost
Ghost::Ghost()
{
	direction = rand() %3;
	countSteps = 0;
	levelBIndication = false;
}

Ghost::Ghost(int _x, int _y)
{
	originalPosition.set(_x, _y);
	position[0] = position[1] = originalPosition;
	direction = rand() % 3;
	countSteps = 0;
	levelBIndication = false;
}

//This function ramdon a number between 1-4 for direction
//Checks the next move is valid (not wall) - If it's a wall, random number until it doesn't
//Checks if the ghost is on pacman position (strike in the game) - update the relevant variables
void Ghost::move(const Point& pac, Fruit* fruitsArr)
{
	setDirection(pac);
	position[1] = position[0]; 
	position[0].move(direction, NOT_PACMAN);

	if (theGame->checkIfTheSamePosition(pac, position[0])) //Checks if the next move is on pacman position
	{
		theGame->setBoardBeforeObjectMoves(position[1]);
		if(theGame->getColored()) //Set color
			setTextColor(LIGHTMAGENTA);
		position[0].draw(DRAW_CHARACTER, GHOST_SYMBOL);
		Sleep(2000);
		setTextColor(WHITE); 
		theGame->ghostAtePacman();
	}

	else if (theGame->isWall(position[1].next(direction, NOT_PACMAN), NOT_PACMAN))
		position[0] = position[1];
	
	else
	{
		for (int i = 0; i < NUM_OF_FRUITS; i++)
		{
			if (theGame->checkIfTheSamePosition(position[0], fruitsArr[i].getCurrentPosition()) && fruitsArr[i].getFruitOnBoard())
			{
				fruitsArr[i].turnOffFruit();
				theGame->updateBoard(position[0]);
			}
		}
		
		theGame->setBoardBeforeObjectMoves(position[1]);
		if(theGame->getColored()) //Set color
			setTextColor(LIGHTMAGENTA);
		position[0].draw(DRAW_CHARACTER, GHOST_SYMBOL); //Draw new position
		position[1] = position[0];
		setTextColor(WHITE);
	}

	countSteps++;
}

void Ghost::setDirection(const Point& pac)
{
	int randRes;
	srand(time(NULL));
	switch (gameLevel)
	{
	case 'a': //BEST level
		chasePacman(pac);
		break;
	case 'b': //GOOD level
		
		if (!levelBIndication) // if levelBIndication is true, it means the ghost is in the 5 steps after the rand direction, stays in the same one
		{
			randRes = rand() % 20 < 1 ? 1 : 0; //random 1 in probability of 1/20
			if (randRes==1) 
			{
				direction = rand() % 3; //random a new direction
				countSteps = 0; //set counter to count 5 steps of the same direction
				levelBIndication = true; //set true to prevent ghost from changing its direction for 5 steps
			}
			else
				chasePacman(pac); //smart ghost
		}
		else if(countSteps == 5) //ghost was on the same direction for 5 steps until now, now becomes a smart ghost
		{
				chasePacman(pac); //smart ghost
				levelBIndication = false; //get out of the 5-same-direction-steps state 
		}	
		break;
	case 'c': //NOVICE level
		if (countSteps == MAX_MOVES || countSteps == 0)
		{
			srand(time(NULL));
			direction = rand() % 3;
			while(theGame->isWall(position[1].next(direction, NOT_PACMAN), NOT_PACMAN))
				direction = rand() % 3;
			countSteps = 0;
		}
		break;
	}
}

void Ghost::setGameLevel(char level)
{
	gameLevel = level;
}

void Ghost::chasePacman(const Point& pac)
{
	int dir, best, curr;
	Point temp = position[0];
	bool firstRound = true;

	for (int i = 0; i < 4; i++) // 4 directions 
	{
		if (!(theGame->isWall(position[1].next(i, NOT_PACMAN), NOT_PACMAN)))
		{
			temp.move(i, NOT_PACMAN);
			if (firstRound)
			{
				dir = i;
				best = temp.getDistance(pac);
				firstRound = false;
			}

			else
			{
				curr = temp.getDistance(pac);
				if (curr < best)
				{
					best = curr;
					dir = i;
				}
			}
			temp = position[0];
		}
	}
	direction = dir;
}

//Empty destructor 
Ghost::~Ghost() {}

