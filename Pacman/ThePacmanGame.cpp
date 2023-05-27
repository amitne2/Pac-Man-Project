#include "ThePacmanGame.h"
#include "_board.h"
#include <string>

using std::ifstream;
using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;

//Constructor
ThePacmanGame::ThePacmanGame(bool coloredGame) : pointsAndLives{ Point(16,24), Point(72, 24) }
{
	numOfBreadcrumbs = 0;
	gameIsOn = true;
	colored = coloredGame; 
}

//This function asks the player to choose the game level.
//Game level affects the ghosts behavior.
//Game level set to all game levels (in default mode)
void ThePacmanGame::checkGameLevel()
{
	clear_screen();
	bool validAnswer = false;
	char game_level;
	cout << "Plase choose game level:" << endl;
	cout << "a - Best" << endl;
	cout << "b - Good" << endl;
	cout << "c - Novice" << endl;

	while (!validAnswer)
	{
		cin >> game_level;
		game_level = tolower(game_level);
		switch (game_level)
		{
		case BEST: //a
			validAnswer = true;
			break;
		case GOOD: //b
			validAnswer = true;
			break;
		case NOVICE: //c
			validAnswer = true;
			break;
		default:
			cout << "WRONG KEY! PLEASE CHOOSE AGAIN - A/B/C." << endl;
			Sleep(1000);
			break;
		}
	}
	clear_screen();
	gameLevel = game_level;
}

//Get colored data - if true - user chose the colored game, if false - user chose no color game.
bool ThePacmanGame::getColored() const
{
	return colored;
}
//Return the left lives in the game
int ThePacmanGame::getPacmanLives() const
{
	return pac.getLives();
}
//Return the points the player earned
int ThePacmanGame::getPacmanPoints() const
{
	return pac.getPoints();
}

//This function returns the game level
char ThePacmanGame::getGameLevel()
{
	return gameLevel;
}

//This function setes the game level
void ThePacmanGame::setGameLevel(char level)
{
	gameLevel = level;
}

//This function copy the points and lives row and add it to board
void ThePacmanGame::copyPointsAndLivesRow(const char* boardToCopy[ROWS])
{
	int k = ROWS - 2;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			board[k+i][j] = boardToCopy[i][j];
		}
		board[i][COLS] = '\0';
	}
}

//This function sets the breadcrumbs on the board to the way there were before there was a strike.
void ThePacmanGame::setBoardBeforeObjectMoves(const Point& p) const
{
	p.draw(DRAW_CHARACTER, board[p.getY()][p.getX()]);
}

void ThePacmanGame::subtractBreadcrumbs()
{
	numOfBreadcrumbs--;
}

//Draw pacman and ghosts according to their places. If user chose a colorful game - function will 
//draww in color. Otherwise - it will draw in white.
void ThePacmanGame::drawObjects()
{
	if (colored)
		setTextColor(YELLOW);
	pac.getCurrentPosition().draw(DRAW_CHARACTER, PACMAN_SYMBOL);
	updateBoard(pac.getCurrentPosition());
	if (colored)
		setTextColor(LIGHTMAGENTA);
	for(int i=0; i<ghosts.size(); i++)
		ghosts[i].getCurrentPosition().draw(DRAW_CHARACTER, GHOST_SYMBOL);
	if(colored)
		setTextColor(LIGHTGREEN);
	for (int i = 0; i < NUM_OF_FRUITS; i++)
	{
		if (fruits[i].getFruitOnBoard())
			fruits[i].getCurrentPosition().draw(DRAW_CHARACTER, fruits[i].getFruitSymbol());
	}
	setTextColor(WHITE);
}

//This fucntion reads a board from file 
//Update the num of Breadcrumbs on this board
//Update objects locations
void ThePacmanGame::initBoardFromFile(const string file_name)
{
	char c;
	string line;
	ifstream screenFile(file_name, std::ios_base::in);
	
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			screenFile.get(c);
			if (c == '%')
				board[i][j] = ' ';
			else if (c == '@')
			{
				board[i][j] = ' ';
				pac.setOriginalPosition(j, i);
			}
			else if (c == '$')
			{
				board[i][j] = '.';
				numOfBreadcrumbs++;
				ghosts.push_back(Ghost(j, i));
			}
			else
			{
				board[i][j] = c;
				if(board[i][j] == '.')
					numOfBreadcrumbs++;
			}
		}
		screenFile.get(c); //get \n
	}
	screenFile.close();
}

//This function draws the board for the first time, in color or without color (depends on user's choice)
//then sets the pacman objects.
void ThePacmanGame::init()
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			gotoxy(j, i);
			if (i == 24 && j == 16 && colored) //color lives
				setTextColor(LIGHTRED);
			if (i == 24 && j == 72 && colored) //color points
				setTextColor(LIGHTGREEN);
			if(board[i][j] == '#' && colored)
				setTextColor(CYAN);
			cout << board[i][j];
			cout.flush();
			setTextColor(WHITE);
		}
		//board[i][COLS] = '\0';// ######need to check if we still need it!!!!!!
	}

	pac.setGame(this);
	for(int i=0; i<ghosts.size(); i++)
		ghosts[i].setGame(this);
	for (int i = 0; i < NUM_OF_FRUITS; i++)
	{
		fruits[i].setGame(this);
		fruits[i].setFruitPosition(pac.getCurrentPosition(), ghosts);
		fruits[i].setFruitOnBoard(false); ///////////////////////////////// added because fruit was set on true
	}
	drawObjects();
}

//This function rucs the game, as long as the pacman is not eaten by the ghosts or as long as the all the points
//are not collected. 
void ThePacmanGame::run()
{
	char key = 0;
	int dir, countPacMoves = 0;
	do
	{
		if (_kbhit())
		{
			key = _getch();
			if (key == ESC)
				initAfterPause();

			key = tolower(key);
			if ((dir = pac.getDirection(key)) != -1)
				pac.setDirection(dir);
		}
		
		pac.move();
		if (colored)
			setTextColor(LIGHTGREEN);
		pointsAndLives[1].draw(pac.getPoints(), DRAW_NUMBER); //draw points
		setTextColor(WHITE);
		countPacMoves++;

		if (countPacMoves % 2 == 0 && gameIsOn)
		{
			for (int i = 0; i < ghosts.size() && gameIsOn; i++)
				ghosts[i].move(pac.getCurrentPosition(), fruits);
			
			if (countPacMoves == 10)
			{
				manageFruits();
				for (int i = 0; i < NUM_OF_FRUITS; i++)
				{
					if (fruits[i].getFruitOnBoard())
						fruits[i].move(pac.getCurrentPosition(), ghosts);
				}
				countPacMoves = 0;
			}
		}

		if (numOfBreadcrumbs == 0)
			gameIsOn = false;

		Sleep(250);
	} while (gameIsOn);
}

//This function starts the game - calls all the initializing functions.
void ThePacmanGame::start(const string file_name)
{
	clear_screen();
	initBoardFromFile(file_name);
	copyPointsAndLivesRow(points_lives_row);
	init();
	run();
}


//Initialize the game after pressing ESC for pause - return all the objects to their places before the ESC
//button was pressed.
void ThePacmanGame::initAfterPause()
{
	char key;
	clear_screen();
	pauseMessage();
	key = _getch();
	while (key != ESC)
	{
		key = _getch();
	}
	clear_screen();

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			gotoxy(j, i);
			if (i == 24 && j == 16 && colored) //color lives
				setTextColor(LIGHTRED);
			if (i == 24 && j == 72 && colored) //color points
				setTextColor(LIGHTGREEN);
			if (board[i][j] == '#' && colored)
				setTextColor(CYAN);
			cout << board[i][j];
			cout.flush();
			setTextColor(WHITE);
		}
	}

	drawObjects();
}

//Update board after pacman "eats" a breadcrumb, to save the data.
void ThePacmanGame::updateBoard(const Point& p)
{
	if (board[p.getY()][p.getX()] == '.') ////////////////////////// new! see if works
		subtractBreadcrumbs();
	board[p.getY()][p.getX()] = ' ';
}

//Check if the next move of the current object is a wall.
//Pacman can go through tunnels - ghost can not, so the check is different.
bool ThePacmanGame::isWall(const Point& p, int object) const
{
	if (object == PACMAN)
	{
		if (board[p.getY()][p.getX()] == '#') // If pacman hits a wall
			return true;
		return false;
	}

	else // other object
	{
		if ((isOnBorder(p)) || (board[p.getY()][p.getX()] == '#'))
			return true;
		return false;
	}
}

//Check if the next move is a breadcrumb, return true if it is, false if it is not.
bool ThePacmanGame::isBreadCrumbs(const Point& p) const // This point is the next move
{
	char sign = board[p.getY()][p.getX()];
	if (sign == ' ' || sign == GHOST_SYMBOL || sign == '#')
		return false;
	return true;
}

//Check if the pacman and the ghost are in the same position at the moment.
bool ThePacmanGame::isGhost()
{
	for (int i = 0; i < ghosts.size(); i++)
		if (checkIfTheSamePosition(pac.getCurrentPosition(), ghosts[i].getCurrentPosition()))
			return true;
	return false;
}
//This function checks if pacman eats fruit and 
//updates the points and turn off the fruit from the board
void ThePacmanGame::isFruit()
{
	for (int i = 0; i < NUM_OF_FRUITS; i++)
		if (checkIfTheSamePosition(pac.getCurrentPosition(), fruits[i].getCurrentPosition()))
		{
			pacmanAteFruit(fruits[i].getFruitSymbol() - '0');
			fruits[i].turnOffFruit();
			updateBoard(pac.getCurrentPosition());
		}
}

//Check if the next move of the ghost is on the game boarders (including tunnels!).
bool ThePacmanGame::isOnBorder(const Point& p) const
{
	if (p.getY() < 0 || p.getY() > 23 || p.getX() < 0 || p.getX() > 79)
		return true;
	return false;
}

//The function Gets 2 points and checks if the points are the same.
bool ThePacmanGame::checkIfTheSamePosition(const Point& p1, const Point& p2) const
{
	if (p1.getX() == p2.getX() && p1.getY() == p2.getY())
		return true;
	return false;
}
//This function manage fruits on board 
// random numOfWantedFruits between the fruits not on board and turn on fruits
//and random their locations
void ThePacmanGame::manageFruits()
{
	int numOfWantedFruits;
	int currFruits = 0;

	for (int i = 0; i < NUM_OF_FRUITS; i++)
		if (fruits[i].getFruitOnBoard())
			currFruits++;
	
	if (currFruits == NUM_OF_FRUITS) 
		return;

	numOfWantedFruits = rand() % (NUM_OF_FRUITS - currFruits);
	for (int i = 0; i < NUM_OF_FRUITS; i++)
	{
		if (!fruits[i].getFruitOnBoard() && numOfWantedFruits>0) //fruit is not on board
		{
			fruits[i].setFruitPosition(pac.getCurrentPosition(), ghosts); //set fruit on board
			fruits[i].setFruitSymbol();
			fruits[i].setDisplayCounter();
			fruits[i].setFruitOnBoard(true);
			numOfWantedFruits--;
		}
	}
}

//Handle the occasion of ghost eating the pacman.
//Set the objects to their initial places and keep the board as it was (meaning breadcrumbs).
//If the pacman has no lives - update gameIsOn to false, so the game will end in the calling funtion.
void ThePacmanGame::ghostAtePacman()
{
	pac.setLives();
	if (pac.getLives() != 0)
	{
		for (int i = 0; i < ghosts.size(); i++)
			setBoardBeforeObjectMoves(ghosts[i].getCurrentPosition());
		pac.resetOriginalPosition();
		pac.setDirection(STAY);
		for(int i=0; i<ghosts.size(); i++)
			ghosts[i].resetOriginalPosition();
		drawObjects();
		if (colored)
			setTextColor(LIGHTRED);
		pointsAndLives[0].draw(pac.getLives(), DRAW_CHARACTER);
		setTextColor(WHITE);
	}

	else
		gameIsOn = false;
}

//This function updates pacman earned points after eating a fruit, then updates the board
void ThePacmanGame::pacmanAteFruit(int fruitPoints)
{
	pac.setPoints(fruitPoints);
	pointsAndLives[1].draw(pac.getPoints(), DRAW_NUMBER);
	//if (isBreadCrumbs(pac.getCurrentPosition()))
		//subtractBreadcrumbs(); //////////////////////////////delete if works
}

//This function prepares the ThePacmanGame parameters for the next screen.
//Positions will not be changes here, because they are set in initBoardFromFile function.
void ThePacmanGame::prepareGameForNextScreen()
{
	pac.setDirection(STAY);
	for (int i = 0; i < ghosts.size(); i++)
		ghosts.pop_back();
	ghosts.resize(0); ////////////////////check if relevant!!! because there were more ghosts than shold be
	for (int i = 0; i < NUM_OF_FRUITS; i++)
		fruits[i].turnOffFruit();
	numOfBreadcrumbs = 0;
	gameIsOn = true;
}

//This function prints the PAUSE message.
void ThePacmanGame::pauseMessage() const
{
	cout << " ____ ____ ____ ____ ____ _________ _________ ____ ____ ____ ____" << endl;
	cout << "||P |||A |||U |||S |||E |||       |||       |||G |||A |||M |||E ||" << endl;
	cout << "||__|||__|||__|||__|||__|||_______|||_______|||__|||__|||__|||__||" << endl;
	cout << "|/__\\|/__\\|/__\\|/__\\|/__\\|/_______\\|/_______\\|/__\\|/__\\|/__\\|/__\\|" << endl;
	cout << endl << "Press 'ESC' to return to the game." << endl;
}
