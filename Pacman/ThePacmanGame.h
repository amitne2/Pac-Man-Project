#ifndef _THEPACMANGAME_H_
#define _THEPACMANGAME_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "io_utils.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Fruit.h"

using std::ifstream;
using std::string;
using std::vector;

enum { ROWS = 26, COLS = 80 };
#define NUM_OF_BREAD_CRUMBS 450
#define NUM_OF_GHOSTS 2
#define NUM_OF_FRUITS 3
#define PACMAN 1
#define NOT_PACMAN 0
#define WIN 1
#define LOSE 0
#define DRAW_CHARACTER -1
#define DRAW_NUMBER 1

class ThePacmanGame {
	enum { ESC = 27 };
	Pacman pac;
	vector<Ghost> ghosts;
	//Ghost ghosts[2];
	Fruit fruits[3];
	Point pointsAndLives[2];
	//char originalBoard[ROWS][COLS + 1];	// this is the original board that we got (we need COLS+1 because we handle it as null terminated char*)
	char board[ROWS][COLS + 1];	// this is the actual board we play on, i.e.
	int numOfBreadcrumbs;
	bool gameIsOn;
	bool colored;
							
public:
	ThePacmanGame(bool coloredGame);
	void checkGameLevel();
	bool getColored();
	//void setBoard(const char* boardToCopy[ROWS]);
	void setBoardBeforeObjectMoves(const Point& p);
	void drawObjects();
	void initBoardFromFile(const string file_name);
	void init();
	void run();
	void start(const string file_name);
	void initAfterPause();
	void updateBoard(const Point& p);
	bool isWall(const Point& p, int object);
	bool isBreadCrumbs(const Point& p);
	bool isGhost();
	void isFruit();
	bool isOnBorder(const Point& p);
	bool checkIfTheSamePosition(const Point& p1, const Point& p2);
	void manageFruits();
	void ghostAtePacman();
	void pacmanAteFruit(int fruitPoints);
	void gameResult(char ch);
	void printGameOver();
	void printWinningMessage();
	void pauseMessage();
	~ThePacmanGame() {}; //Distructor
};

#endif
