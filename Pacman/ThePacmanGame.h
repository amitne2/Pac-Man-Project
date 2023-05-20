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

enum { ROWS = 26, COLS = 80 };
enum {UP, DOWN, LEFT, RIGHT, STAY};

#define NUM_OF_FRUITS 3

enum {NOT_PACMAN, PACMAN};
enum {BEST = 'a', GOOD = 'b', NOVICE = 'c' };
//#define PACMAN 1
//#define NOT_PACMAN 0
//#define WIN 1
//#define LOSE 0
#define DRAW_CHARACTER -1
#define DRAW_NUMBER 1
#define DEFAULT_DIRECTION 3

class ThePacmanGame {
	enum { ESC = 27 };
	Pacman pac;
	std::vector<Ghost> ghosts;
	//Ghost ghosts[2];
	Fruit fruits[NUM_OF_FRUITS];
	Point pointsAndLives[2];
	//char originalBoard[ROWS][COLS + 1];	// this is the original board that we got (we need COLS+1 because we handle it as null terminated char*)
	char board[ROWS][COLS + 1];	// this is the actual board we play on, i.e.
	int numOfBreadcrumbs;
	bool gameIsOn;
	bool colored;
	//bool screen_is_default;
							
public:
	ThePacmanGame(bool coloredGame);
	//ThePacmanGame(bool coloredGame, int _lives);
	void checkGameLevel();
	bool getColored();
	int getPacmanLives();
	int getPacmanPoints();
	void copyPointsAndLivesRow(const char* points_lives_row[ROWS]);
	void setBoardBeforeObjectMoves(const Point& p);
	void setBreadcrumbs();
	//void setScreenMode(bool _mode);
	void drawObjects();
	void initBoardFromFile(const std::string file_name);
	void init();
	void run();
	void start(const std::string file_name);
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
	void prepareGameForNextScreen();
	//void gameResult(char ch);
	//void printGameOver();
	//void printWinningMessage();
	void pauseMessage();
	~ThePacmanGame() {}; //Distructor
};

#endif
