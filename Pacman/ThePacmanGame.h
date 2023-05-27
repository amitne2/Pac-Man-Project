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
enum {NOT_PACMAN, PACMAN};
enum {BEST = 'a', GOOD = 'b', NOVICE = 'c' };

constexpr int NUM_OF_FRUITS = 3;
constexpr int DRAW_CHARACTER = -1;
constexpr int DRAW_NUMBER = 1;
constexpr int DEFAULT_DIRECTION = 3;

class ThePacmanGame {
	enum { ESC = 27 };
	Pacman pac;
	std::vector<Ghost> ghosts;
	Fruit fruits[NUM_OF_FRUITS];
	Point pointsAndLives[2];
	char board[ROWS][COLS + 1];	
	int numOfBreadcrumbs;
	bool gameIsOn;
	bool colored;
	char gameLevel;
							
public:
	ThePacmanGame(bool coloredGame);
	void checkGameLevel();
	bool getColored() const;
	int getPacmanLives() const;
	int getPacmanPoints() const;
	char getGameLevel();
	void setGameLevel(char level);
	void copyPointsAndLivesRow(const char* points_lives_row[ROWS]);
	void setBoardBeforeObjectMoves(const Point& p) const;
	void subtractBreadcrumbs();
	void drawObjects();
	void initBoardFromFile(const std::string file_name);
	void init();
	void run();
	void start(const std::string file_name);
	void initAfterPause();
	void updateBoard(const Point& p);
	bool isWall(const Point& p, int object) const;
	bool isBreadCrumbs(const Point& p) const;
	bool isGhost() const; 
	void isFruit(); 
	bool isOnBorder(const Point& p) const;
	bool checkIfTheSamePosition(const Point& p1, const Point& p2) const;
	void manageFruits();
	void ghostAtePacman();
	void pacmanAteFruit(int fruitPoints);
	void prepareGameForNextScreen();
	void pauseMessage() const;
	~ThePacmanGame() {}; //Distructor
};

#endif
