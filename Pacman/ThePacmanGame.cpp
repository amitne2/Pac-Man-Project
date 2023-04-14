#include "ThePacmanGame.h"

void ThePacmanGame::handleObjectCreationFromBoard(int row, int col)
{
	static int countGhosts = 0;
	char ch = board[row][col];
	if (ch == '@')
		pac.setPosition(row, col);
	if (ch == '$')
	{
		ghosts[countGhosts].setPosition(row, col);
		countGhosts++;
	}
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

//void ThePacmanGame::drawOnBoard(const Point& p, char c)
//{
//	board[p.getY()][p.getX()] = c;
//}

//char ThePacmanGame::getBoardSignInPosition(const Point& p)
//{
//	return board[p.getY()][p.getX()];
//}

bool ThePacmanGame::isFruit(const Point& p) // This point is the next move
{
	char sign = board[p.getY()][p.getX()];
	if (sign == ' ' || sign == '$' || sign == '+')
		return false;
	return true;
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
			handleObjectCreationFromBoard(i, j);
		}
		board[i][COLS] = '\0';
	}

	pac.setGame(this);
	ghosts[0].setGame(this);
	ghosts[1].setGame(this);
	pac.setArrowKeys("wxads");
}

void ThePacmanGame::run()
{
	char key = 0;
	int dir;
	do
	{
		if (_kbhit())
		{
			key = _getch();
			if ((dir = pac.getDirection(key)) != -1)
				pac.setDirection(dir);
		}
		pac.move();
		ghosts[0].move();
		ghosts[1].move();
		//if pacman moves 2 steps
		//ghosts move
		Sleep(400);
	} while (key != ESC);
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
