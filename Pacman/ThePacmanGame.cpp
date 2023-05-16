#include "ThePacmanGame.h"
#include "_board.h"
#include <string>

//Constructor
ThePacmanGame::ThePacmanGame(bool coloredGame) : pointsAndLives{ Point(16,24), Point(72, 24) }
{
	numOfBreadcrumbs = 0;
	gameIsOn = true;
	colored = coloredGame;
	//screen_is_default = true; //load screens as long as user is winning
}


////Constructor
//ThePacmanGame::ThePacmanGame(bool coloredGame, int _lives) : pac(_lives), pointsAndLives{ Point(16,24), Point(72, 24) }
//{
//	numOfBreadcrumbs = 0;
//	gameIsOn = true;
//	colored = coloredGame;
//	default_mode = true; //load screens as long as user is winning
//	screen_num = 1;
//}

//This function asks the player to choose the game level.
//Game level affects the ghosts behavior.
void ThePacmanGame::checkGameLevel()
{
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
		case 'a':
			validAnswer = true;
			break;
		case 'b':
			validAnswer = true;
			break;
		case 'c':
			validAnswer = true;
			break;
		default:
			cout << "WRONG KEY! PLEASE CHOOSE AGAIN - A/B/C." << endl;
			Sleep(1000);
			break;
		}
	}
	clear_screen();
	for (int i = 0; i < ghosts.size(); i++)
		ghosts[i].setGameLevel(game_level);
}

//Get colored data - if true - user chose the colored game, if false - user chose no color game.
bool ThePacmanGame::getColored()
{
	return colored;
}

int ThePacmanGame::getPacmanLives()
{
	return pac.getLives();
}

int ThePacmanGame::getPacmanPoints()
{
	return pac.getPoints();
}

////This function sets the game board - copies from const board to original.
//void ThePacmanGame::setBoard(const char* boardToCopy[ROWS])
//{
//	for (int i = 0; i < ROWS; i++)
//	{
//		for (int j = 0; j < COLS; j++)
//		{
//			originalBoard[i][j] = boardToCopy[i][j];
//		}
//		originalBoard[i][COLS] = '\0';
//	}
//}

//This function sets the breadcrumbs on the board to the way there were before there was a strike.
void ThePacmanGame::setBoardBeforeObjectMoves(const Point& p)
{
	p.draw(DRAW_CHARACTER, board[p.getY()][p.getX()]);
}

void ThePacmanGame::setBreadcrumbs()
{
	numOfBreadcrumbs--;
}

//void ThePacmanGame::setScreenMode(bool _mode)
//{
//	screen_is_default = _mode;
//}

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
		setTextColor(LIGHTMAGENTA);
	for (int i = 0; i < NUM_OF_FRUITS; i++)
	{
		if (fruits[i].getFruitOnBoard())
			fruits[i].getCurrentPosition().draw(DRAW_CHARACTER, fruits[i].getFruitSymbol());
	}
	setTextColor(WHITE);
}

void ThePacmanGame::initBoardFromFile(const string file_name)
{
	char c;
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
				numOfBreadcrumbs++;
			}
		}
		screenFile.get(c); //get \n
	}
	screenFile.close();
	checkGameLevel();
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
		board[i][COLS] = '\0';
	}

	pac.setGame(this);
	for(int i=0; i<ghosts.size(); i++)
		ghosts[i].setGame(this);
	for (int i = 0; i < NUM_OF_FRUITS; i++)
	{
		fruits[i].setGame(this);
		fruits[i].setFruitPosition(pac.getCurrentPosition(), ghosts);
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
	//setBoard(board_example);
	initBoardFromFile(file_name);
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
		board[i][COLS] = '\0';
	}

	drawObjects();
}

//Update board after pacman "eats" a breadcrumb, to save the data.
void ThePacmanGame::updateBoard(const Point& p)
{
	board[p.getY()][p.getX()] = ' ';
}

//Check if the next move of the current object is a wall.
//Pacman can go through tunnels - ghost can not, so the check is different.
bool ThePacmanGame::isWall(const Point& p, int object)
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
bool ThePacmanGame::isBreadCrumbs(const Point& p) // This point is the next move
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
bool ThePacmanGame::isOnBorder(const Point& p)
{
	if (p.getY() < 0 || p.getY() > 24 || p.getX() < 0 || p.getX() > 80)
		return true;
	return false;
}

//Check if the points are the same.
bool ThePacmanGame::checkIfTheSamePosition(const Point& p1, const Point& p2)
{
	if (p1.getX() == p2.getX() && p1.getY() == p2.getY())
		return true;
	return false;
}

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
			fruits[i].setFruitPosition(pac.getCurrentPosition(), ghosts);
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
		pac.setDirection(3);
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
}

//This function prepares the ThePacmanGame parameters for the next screen.
//Positions will not be changes here, because they are set in initBoardFromFile function.

void ThePacmanGame::prepareGameForNextScreen()
{
	pac.setDirection(DEFAULT_DIRECTION);
	for (int i = 0; i < ghosts.size(); i++)
		ghosts.pop_back();
	for (int i = 0; i < NUM_OF_FRUITS; i++)
		fruits[i].turnOffFruit();
	numOfBreadcrumbs = 0;
}

////Print the right message according to game result.
//void ThePacmanGame::gameResult(char ch)
//{
//	clear_screen();
//	if (ch)
//		printWinningMessage();
//	else
//		printGameOver();
//
//	Sleep(1000);
//	_getch();
//	clear_screen();
//}


////This function prints the GAME OVER message.
//void ThePacmanGame::printGameOver()
//{
//	if(colored)
//		setTextColor(LIGHTRED);
//	cout << "######       ###    ##     ## ########     #######  ##     ## ######## ########   ####  ####" << endl;
//	cout << "##    ##    ## ##   ###   ### ##          ##     ## ##     ## ##       ##     ##  ####  ####" << endl;
//	cout << "##         ##   ##  #### #### ##          ##     ## ##     ## ##       ##     ##  ####  ####" << endl;
//	cout << "##   #### ##     ## ## ### ## ######      ##     ## ##     ## ######   ########    ##    ##" << endl;
//	cout << "##    ##  ######### ##     ## ##          ##     ##  ##   ##  ##       ##   ## "<< endl;
//	cout << "##    ##  ##     ## ##     ## ##          ##     ##   ## ##   ##       ##    ##   ####  ####" << endl;
//	cout << "######    ##     ## ##     ## ########     #######     ###    ######## ##     ##  ####  ####" << endl;
//	setTextColor(WHITE);
//
//	cout << endl << "# Press any key on your keyboard to go back to the menu." << endl;
//
//}
//
////This function prints the WINNER message.
//void ThePacmanGame::printWinningMessage()
//{
//	if (colored)
//		setTextColor(MAGENTA);
//	cout << "##      ## #### ##    ## ##    ## ######## ########  #### ####" << endl;
//	cout << "##  ##  ##  ##  ###   ## ###   ## ##       ##     ## #### ####" << endl;
//	cout << "##  ##  ##  ##  ####  ## ####  ## ##       ##     ## #### ####" << endl;
//	cout << "##  ##  ##  ##  ## ## ## ## ## ## ######   ########   ##   ##" << endl;
//	cout << "##  ##  ##  ##  ##  #### ##  #### ##       ##   ##" << endl;
//	cout << "##  ##  ##  ##  ##   ### ##   ### ##       ##    ##  #### ####" << endl;
//	cout << "###   ###  #### ##    ## ##    ## ######## ##     ## #### ####" << endl;
//	setTextColor(WHITE);
//	cout << endl << "# Press any key on your keyboard to go back to the menu." << endl;
//}

//This function prints the PAUSE message.
void ThePacmanGame::pauseMessage()
{
	cout << " ____ ____ ____ ____ ____ _________ _________ ____ ____ ____ ____" << endl;
	cout << "||P |||A |||U |||S |||E |||       |||       |||G |||A |||M |||E ||" << endl;
	cout << "||__|||__|||__|||__|||__|||_______|||_______|||__|||__|||__|||__||" << endl;
	cout << "|/__\\|/__\\|/__\\|/__\\|/__\\|/_______\\|/_______\\|/__\\|/__\\|/__\\|/__\\|" << endl;
	cout << endl << "Press 'ESC' to return to the game." << endl;
}
