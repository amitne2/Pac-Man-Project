#include "ThePacmanGame.h"

void ThePacmanGame::handleObjectCreationFromBoard(int row, int col)
{
	char ch = board[row][col];
	if (ch == '@')
		pac.setPosition(row, col);
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
		Sleep(400);
	} while (key != ESC);
}

bool ThePacmanGame::isWall(const Point & p)
{
	if (originalBoard[p.getX()][p.getY()] == '+') // If pacman hit 
		return true;
	return false;
}
