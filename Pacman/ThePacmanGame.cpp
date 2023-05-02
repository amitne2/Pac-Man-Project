#include "ThePacmanGame.h"
#include "_board.h"

//Constructor
ThePacmanGame::ThePacmanGame(bool coloredGame) : pac(8, 40), ghosts{ Ghost(1,57), Ghost(17, 16) }, pointsAndLives{ Point(16,24), Point(72, 24) }
{
	gameIsOn = true;
	colored = coloredGame;
}

//Get colored data - if true - user chose the colored game, if false - user chose no color game.
bool ThePacmanGame::getColored()
{
	return colored;
}

//This function sets the game board - copies from const board to original.
void ThePacmanGame::setBoard(const char* boardToCopy[ROWS])
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			originalBoard[i][j] = boardToCopy[i][j];
		}
		originalBoard[i][COLS] = '\0';
	}
}

//This function sets the breadcrumbs on the board to the way there were before there was a strike.
void ThePacmanGame::setBoardBeforeStrike(const Point& p)
{
	p.draw(DRAW_CHARACTER, board[p.getY()][p.getX()]);
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
	ghosts[0].getCurrentPosition().draw(DRAW_CHARACTER, GHOST_SYMBOL);
	ghosts[1].getCurrentPosition().draw(DRAW_CHARACTER, GHOST_SYMBOL);
	setTextColor(WHITE);
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
			if(originalBoard[i][j] == '+' && colored)
				setTextColor(CYAN);
			cout << originalBoard[i][j];
			cout.flush();
			setTextColor(WHITE);
			board[i][j] = originalBoard[i][j];
		}
		board[i][COLS] = '\0';
	}

	pac.setGame(this);
	ghosts[0].setGame(this);
	ghosts[1].setGame(this);
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

		if (countPacMoves == 2 && gameIsOn)
		{
			for (int i = 0; i < 2 && gameIsOn; i++)
				ghosts[i].move(pac.getCurrentPosition());
			countPacMoves = 0;
		}

		if (pac.getPoints() == NUM_OF_BREAD_CRUMBS)
		{
			gameResult(WIN);
			gameIsOn = false;
		}

		Sleep(250);
	} while (gameIsOn);

	if (pac.getLives() == 0)
		gameResult(LOSE);

}

//This function starts the game - calls all the initializing functions.
void ThePacmanGame::start()
{
	clear_screen();
	setBoard(board_example);
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
			if (originalBoard[i][j] == '+' && colored)
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
		if (board[p.getY()][p.getX()] == '+') // If pacman hits a wall
			return true;
		return false;
	}

	else // object is GHOST
	{
		if ((isOnBorder(p)) || (board[p.getY()][p.getX()] == '+'))
			return true;
		return false;
	}
}

//Check if the next move is a breadcrumb, return true if it is, false if it is not.
bool ThePacmanGame::isBreadCrumbs(const Point& p) // This point is the next move
{
	char sign = board[p.getY()][p.getX()];
	if (sign == ' ' || sign == '$' || sign == '+')
		return false;
	return true;
}

//Check if the pacman and the ghost are in the same position at the moment.
bool ThePacmanGame::isGhost()
{
	if(checkIfTheSamePosition(pac.getCurrentPosition(), ghosts[0].getCurrentPosition()) || checkIfTheSamePosition(pac.getCurrentPosition(), ghosts[1].getCurrentPosition()))
		return true;
	return false;
}

//Check if the next move of the ghost is on the game boarders (including tunnels!).
bool ThePacmanGame::isOnBorder(const Point& p)
{
	if (p.getY() < 1 || p.getY() > 23 || p.getX() < 1 || p.getX() > 79)
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

//Handle the occasion of ghost eating the pacman.
//Set the objects to their initial places and keep the board as it was (meaning breadcrumbs).
//If the pacman has no lives - update gameIsOn to false, so the game will end in the calling funtion.
void ThePacmanGame::ghostAtePacman()
{
	pac.setLives();
	if (pac.getLives() != 0)
	{
		setBoardBeforeStrike(ghosts[0].getCurrentPosition());
		setBoardBeforeStrike(ghosts[1].getCurrentPosition());
		pac.setOriginalPosition();
		pac.setDirection(3);
		ghosts[0].setOriginalPosition();
		ghosts[1].setOriginalPosition();
		drawObjects();
		if (colored)
			setTextColor(LIGHTRED);
		pointsAndLives[0].draw(pac.getLives(), DRAW_CHARACTER);
		setTextColor(WHITE);
	}

	else
		gameIsOn = false;
}

//Print the right message according to game result.
void ThePacmanGame::gameResult(char ch)
{
	clear_screen();
	if (ch)
		printWinningMessage();
	else
		printGameOver();

	Sleep(1000);
	_getch();
	clear_screen();
}


//This function prints the GAME OVER message.
void ThePacmanGame::printGameOver()
{
	if(colored)
		setTextColor(LIGHTRED);
	cout << "######       ###    ##     ## ########     #######  ##     ## ######## ########   ####  ####" << endl;
	cout << "##    ##    ## ##   ###   ### ##          ##     ## ##     ## ##       ##     ##  ####  ####" << endl;
	cout << "##         ##   ##  #### #### ##          ##     ## ##     ## ##       ##     ##  ####  ####" << endl;
	cout << "##   #### ##     ## ## ### ## ######      ##     ## ##     ## ######   ########    ##    ##" << endl;
	cout << "##    ##  ######### ##     ## ##          ##     ##  ##   ##  ##       ##   ## "<< endl;
	cout << "##    ##  ##     ## ##     ## ##          ##     ##   ## ##   ##       ##    ##   ####  ####" << endl;
	cout << "######    ##     ## ##     ## ########     #######     ###    ######## ##     ##  ####  ####" << endl;
	setTextColor(WHITE);

	cout << endl << "# Press any key on your keyboard to go back to the menu." << endl;

}

//This function prints the WINNER message.
void ThePacmanGame::printWinningMessage()
{
	if (colored)
		setTextColor(MAGENTA);
	cout << "##      ## #### ##    ## ##    ## ######## ########  #### ####" << endl;
	cout << "##  ##  ##  ##  ###   ## ###   ## ##       ##     ## #### ####" << endl;
	cout << "##  ##  ##  ##  ####  ## ####  ## ##       ##     ## #### ####" << endl;
	cout << "##  ##  ##  ##  ## ## ## ## ## ## ######   ########   ##   ##" << endl;
	cout << "##  ##  ##  ##  ##  #### ##  #### ##       ##   ##" << endl;
	cout << "##  ##  ##  ##  ##   ### ##   ### ##       ##    ##  #### ####" << endl;
	cout << "###   ###  #### ##    ## ##    ## ######## ##     ## #### ####" << endl;
	setTextColor(WHITE);
	cout << endl << "# Press any key on your keyboard to go back to the menu." << endl;
}

//This function prints the PAUSE message.
void ThePacmanGame::pauseMessage()
{
	cout << " ____ ____ ____ ____ ____ _________ _________ ____ ____ ____ ____" << endl;
	cout << "||P |||A |||U |||S |||E |||       |||       |||G |||A |||M |||E ||" << endl;
	cout << "||__|||__|||__|||__|||__|||_______|||_______|||__|||__|||__|||__||" << endl;
	cout << "|/__\\|/__\\|/__\\|/__\\|/__\\|/_______\\|/_______\\|/__\\|/__\\|/__\\|/__\\|" << endl;
	cout << endl << "Press 'ESC' to return to the game." << endl;
}
