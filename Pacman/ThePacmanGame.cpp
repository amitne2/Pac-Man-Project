#include "ThePacmanGame.h"
#include "_board.h"

ThePacmanGame::ThePacmanGame(bool coloredGame) : pac(4, 40), ghosts{ Ghost(4,43), Ghost(1, 44) }, pointsAndLives{ Point(16,24), Point(72, 24) }
{
	gameIsOn = true;
	colored = coloredGame;
}

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

void ThePacmanGame::updateBoard(const Point& p)
{
	board[p.getY()][p.getX()] = ' ';
}

void ThePacmanGame:: setBoardBeforeStrike(const Point& p)
{
	p.draw(DRAW_CHARACTER, board[p.getY()][p.getX()]);
}

bool ThePacmanGame::getColored()
{
	return colored;
}


bool ThePacmanGame::isBreadCrumbs(const Point& p) // This point is the next move
{
	char sign = board[p.getY()][p.getX()];
	if (sign == ' ' || sign == '$' || sign == '+')
		return false;
	return true;
}

bool ThePacmanGame::isGhost()
{
	if(checkIfTheSamePosition(pac.getCurrentPosition(), ghosts[0].getCurrentPosition()) || checkIfTheSamePosition(pac.getCurrentPosition(), ghosts[1].getCurrentPosition()))
		return true;
	return false;
}

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



void ThePacmanGame::init()
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			gotoxy(j, i);
			if(i==24 && j==16 && colored)
				setTextColor(LIGHTRED);
			if(i==24 && j==72 && colored)
				setTextColor(LIGHTGREEN);
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

void ThePacmanGame::pauseMessage()
{
	cout << " ____ ____ ____ ____ ____ _________ _________ ____ ____ ____ ____" << endl;
	cout << "||P |||A |||U |||S |||E |||       |||       |||G |||A |||M |||E ||" << endl;
	cout << "||__|||__|||__|||__|||__|||_______|||_______|||__|||__|||__|||__||" << endl;
	cout << "|/__\\|/__\\|/__\\|/__\\|/__\\|/_______\\|/_______\\|/__\\|/__\\|/__\\|/__\\|" << endl;

	cout << endl << "Press 'ESC' to return to the game." << endl;
}

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
			if (i == 24 && j == 16 && colored)
				setTextColor(LIGHTRED);
			if (i == 24 && j == 72 && colored)
				setTextColor(LIGHTGREEN);
			cout << board[i][j];
			cout.flush();
			setTextColor(WHITE);
		}
		board[i][COLS] = '\0';
	}

	drawObjects();
}

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
			
			key =tolower(key);
			if ((dir = pac.getDirection(key)) != -1)
				pac.setDirection(dir);
		}
		
		pac.move();
		if(colored)
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
	
		Sleep(400);
	} while (gameIsOn);
		
	if (pac.getLives() == 0)
		gameResult(LOSE);	

}

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

void ThePacmanGame::printWinningMessage()
{
	if(colored)
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

bool ThePacmanGame::isWall(const Point & p, int object)
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

bool ThePacmanGame::isOnBorder(const Point& p)
{
	if (p.getY() < 1 || p.getY() > 24 || p.getX() < 1 || p.getX() > 79)
		return true;
	return false;
}

void ThePacmanGame::drawObjects()
{
	if(colored)
		setTextColor(YELLOW);
	pac.getCurrentPosition().draw(DRAW_CHARACTER, PACMAN_SYMBOL);
	updateBoard(pac.getCurrentPosition());
	if(colored)
		setTextColor(LIGHTBLUE);
	ghosts[0].getCurrentPosition().draw(DRAW_CHARACTER, GHOST_SYMBOL);
	ghosts[1].getCurrentPosition().draw(DRAW_CHARACTER, GHOST_SYMBOL);
	setTextColor(WHITE);
}

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
		if(colored)
			setTextColor(LIGHTRED);
		pointsAndLives[0].draw(pac.getLives(), DRAW_CHARACTER);
		setTextColor(WHITE);
	}

	else
		gameIsOn = false;
}

bool ThePacmanGame::checkIfTheSamePosition(const Point& p1, const Point& p2)
{
	if (p1.getX() == p2.getX() && p1.getY() == p2.getY())
		return true;
	return false;
}

void ThePacmanGame::start() 
{
	clear_screen();
	setBoard(board_example);
	init();
	run();
}

