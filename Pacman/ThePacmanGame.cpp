#include "ThePacmanGame.h"
#include "_game_over_message.h"
#include "_board.h"
#include "_winning_message.h"

//
ThePacmanGame::ThePacmanGame() : pac(4, 40), ghosts{ Ghost(4,43), Ghost(1, 44) }, pointsAndLives{ Point(16,24), Point(72, 24) }
{
	gameIsOn = true;
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

void ThePacmanGame::setBoardBeforeStrike(Point p)
{
	p.draw(board[p.getY()][p.getX()]);
}

//char ThePacmanGame::getBoardSignInPosition(const Point& p)
//{
//	return board[p.getY()][p.getX()];
//}

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
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			gotoxy(j, i);
			cout << game_over[i][j];
			cout.flush();
		}
	}
}

void ThePacmanGame::init()
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			gotoxy(j, i);
			cout << originalBoard[i][j];
			cout.flush();
			board[i][j] = originalBoard[i][j];
		}
		board[i][COLS] = '\0';
	}

	pac.setGame(this);
	ghosts[0].setGame(this);
	ghosts[1].setGame(this);
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
			{
				key = _getch();
				while (key != ESC)
				{
					key = _getch();
				}
			}
			key =tolower(key);
			if ((dir = pac.getDirection(key)) != -1)
				pac.setDirection(dir);
		}
		
		pac.move();
		pointsAndLives[1].draw(pac.getPoints()); //draw points
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
	
	//clear_screen();
	
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
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			gotoxy(j, i);
			cout << winning[i][j];
			cout.flush();
		}
	}
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
	pac.getCurrentPosition().draw('@');
	updateBoard(pac.getCurrentPosition());
	ghosts[0].getCurrentPosition().draw('$');
	ghosts[1].getCurrentPosition().draw('$');
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
		pointsAndLives[0].draw(pac.getLives());
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

