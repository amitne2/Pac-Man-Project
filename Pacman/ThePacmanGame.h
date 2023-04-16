#ifndef _THEPACMANGAME_H_
#define _THEPACMANGAME_H_

#include "io_utils.h"
#include "Pacman.h"
#include "Ghost.h"

enum { ROWS = 26, COLS = 80 };
#define NUM_OF_FRUITS 7
#define PACMAN 1
#define GHOST 0

class ThePacmanGame {
	enum { ESC = 27 };
	Pacman pac;
	Ghost ghosts[2];
	Point pointsAndLives[2];
	char originalBoard[ROWS][COLS + 1];	// this is the original board that we got (we need COLS+1 because we handle it as null terminated char*)
	char board[ROWS][COLS + 1];	// this is the actual board we play on, i.e.
	bool gameIsOn;
								//void handleObjectCreationFromBoard(int row, int col);
public:
	ThePacmanGame();
	void setBoard(const char* boardToCopy[ROWS]);
	void updateBoard(const Point& p);
	void setBoardBeforeStrike(Point p);
	//char getBoardSignInPosition(const Point& p);
	void init();
	void drawObjects();
	bool isWall(const Point& p, int object);
	bool isBreadCrumbs(const Point& p);
	bool isGhost();
	void run();
	bool isOnBorder(const Point& p);
	void ghostAtePacman();
	bool checkIfTheSamePosition(const Point& p1, const Point& p2);
	void printGameOver();
	void start();
};

#endif
