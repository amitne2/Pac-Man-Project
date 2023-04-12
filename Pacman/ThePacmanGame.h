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
	void handleObjectCreationFromBoard(int row, int col);
public:
	void setBoard(const char* boardToCopy[ROWS]);
	//void drawOnBoard(const Point& p, char c);
	char getBoardSignInPosition(const Point& p);
	void init();
	bool isWall(const Point& p);
	void run();
};

#endif
