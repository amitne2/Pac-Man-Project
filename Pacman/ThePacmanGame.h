#ifndef _THEPACMANGAME_H_
#define _THEPACMANGAME_H_

#include "io_utils.h"
#include "Pacman.h"
#include "Ghost.h"

enum { ROWS = 26, COLS = 80 };
#define NUM_OF_BREAD_CRUMBS 1309
#define PACMAN 1
#define GHOST 0
#define WIN 1
#define LOSE 0
#define DRAW_CHARACTER -1
#define DRAW_NUMBER 1

class ThePacmanGame {
	enum { ESC = 27 };
	Pacman pac;
	Ghost ghosts[2];
	Point pointsAndLives[2];
	char originalBoard[ROWS][COLS + 1];	// this is the original board that we got (we need COLS+1 because we handle it as null terminated char*)
	char board[ROWS][COLS + 1];	// this is the actual board we play on, i.e.
	bool gameIsOn;
	bool colored;
							
public:
	ThePacmanGame(bool coloredGame);
	bool getColored();
	void setBoard(const char* boardToCopy[ROWS]);
	void setBoardBeforeStrike(const Point& p);
	void drawObjects();
	void init();
	void run();
	void start();
	void initAfterPause();
	void updateBoard(const Point& p);
	bool isWall(const Point& p, int object);
	bool isBreadCrumbs(const Point& p);
	bool isGhost();
	bool isOnBorder(const Point& p);
	bool checkIfTheSamePosition(const Point& p1, const Point& p2);
	void ghostAtePacman();
	void gameResult(char ch);
	void printGameOver();
	void printWinningMessage();
	void pauseMessage();
	~ThePacmanGame() {}; //Distructor
};

#endif
