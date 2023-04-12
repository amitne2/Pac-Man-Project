#ifndef _THEPACMANGAME_H_
#define _THEPACMANGAME_H_

#include "io_utils.h"
#include "Pacman.h"


enum { ROWS = 24, COLS = 80 };

class ThePacmanGame {
	enum { ESC = 27 };
	Pacman pac;

	char originalBoard[ROWS][COLS + 1];	// this is the original board that we got (we need COLS+1 because we handle it as null terminated char*)
	char board[ROWS][COLS + 1];	// this is the actual board we play on, i.e.
	void handleObjectCreationFromBoard(int row, int col)
	{
		char ch = board[row][col];
		if (ch == '@')
			pac.setPosition(row, col);
	}
public:
	void setBoard(const char* boardToCopy[ROWS])
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

	void init()
	{
		for (int i = 0; i < ROWS; i++)
		{
			for (int j = 0; j < COLS; j++)
			{
				gotoxy(j, i);
				cout << originalBoard[i][j];
				cout.flush();
				board[i][j] = originalBoard[i][j];
				//handleObjectCreationFromBoard(i, j);
			}
			board[i][COLS] = '\0';
		}

		pac.setGame(this);
		pac.setArrowKeys("wxads");
		
	}
	void run()
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
};

#endif
