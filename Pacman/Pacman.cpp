#include "Pacman.h"
#include "ThePacmanGame.h"

//Constructor pacman
Pacman::Pacman()
{
	direction = STAY;
	lives = 3;
	points = 0;
	setArrowKeys("wxads");
}

//This function set the arrow keys of the game
void Pacman::setArrowKeys(const char* keys)
{
	arrowKeys[UP] = keys[UP]; 
	arrowKeys[DOWN] = keys[DOWN];
	arrowKeys[LEFT] = keys[LEFT]; 
	arrowKeys[RIGHT] = keys[RIGHT]; 
	arrowKeys[STAY] = keys[STAY];
}

//This function set lives (remove one each time)
void Pacman::setLives()
{
	lives--;
}

//This function gets key and return the number of this direction
//return a number between 0-4
//return -1 if the key is wrong
int Pacman::getDirection(char key) const
{
	for (int i = 0; i < 5; i++)
	{
		if (key == arrowKeys[i])
			return i;
	}
	return -1;
}
//This function return the lives left in the game
int Pacman::getLives() const
{
	return lives;
}
//This function return the points the pacman earned
int Pacman::getPoints() const
{
	return points;
}

//This function adds the points the pacman earned
void Pacman::setPoints(int _points)
{
	points += _points;
}

//This function gets according to pacman's direction his next move
// if his next move is wall - stays in the same postion (update the direction to stay)
//If his next move is ghost - delete the pacman's position and update the relevant variables 
//If his next move is breadCrumb - add to points
//Update pacman's new position
void Pacman::move()
{
	position[1] = position[0];
	position[0].move(direction, PACMAN); 
	
	if (theGame->isWall(position[1].next(direction, PACMAN), PACMAN)) //Checks if the next move is wall
	{
		direction = STAY; // Pacman stops at wall
		position[0] = position[1]; //Update new position
	}

	else if (theGame->isGhost()) //Checks if the next move is on ghost
	{
		position[1].draw(DRAW_CHARACTER, ' '); //The ghost eats the pacman
		Sleep(2000);
		//if (theGame->isBreadCrumbs(position[0]))
		//	theGame->subtractBreadcrumbs();
		theGame->ghostAtePacman();
	}

	else 
	{
		theGame->isFruit();

		if (direction != STAY) // NOT STAY POSITION
			position[1].draw(DRAW_CHARACTER, ' '); //Set the old position
		if (theGame->isBreadCrumbs(position[0])) //Checks if move is on breadCrumb
		{
			points++;
		}

		if(theGame->getColored()) //Set color
				setTextColor(YELLOW);	
		position[0].draw(DRAW_CHARACTER, PACMAN_SYMBOL); //Draw new pacman's position
		setTextColor(WHITE);
		position[1] = position[0]; 
	}

	theGame->updateBoard(position[1]); //Update board
}

//Empty destructor
Pacman::~Pacman() {}

