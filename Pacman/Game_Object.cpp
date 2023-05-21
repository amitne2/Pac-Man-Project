#include "Game_Object.h"

//Constructor
Game_Object::Game_Object() {} 

//Set the pacmanGame pointer
void Game_Object::setGame(ThePacmanGame* _theGame) 
{
	theGame = _theGame;
}

//Reset current position to original position
void Game_Object::resetOriginalPosition() 
{
	position[0] = position[1] = originalPosition;
}

//Set object's original position
void Game_Object::setOriginalPosition(int _x, int _y) 
{
	originalPosition.set(_x,_y);
	position[0] = position[1] = originalPosition;
}

//this Function return the postion of the object
Point Game_Object::getCurrentPosition() const
{
	return position[0];
}

//This function sets the direction of the game object
void Game_Object::setDirection(int _direction)
{
	direction = _direction;
}

//This function returns the current direction of the game object
int Game_Object::getDirection() const
{
	return direction;
}