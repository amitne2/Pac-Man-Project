#include "ThePacmanGame.h"
#include "_game_over_message.h"
#include "_board.h"

ThePacmanGame::ThePacmanGame() : pac(4, 40), ghosts{ Ghost(4,43), Ghost(1, 44) }, pointsAndLives{ Point(16,24), Point(72, 24) }
{
	gameIsOn = true;
}

//void ThePacmanGame::handleObjectCreationFromBoard(int row, int col)
//{
//	static int countGhosts = 0;
//	char ch = board[row][col];
//	if (ch == '@')
//		pac.setPosition(row, col);
//	if (ch == '$')
//	{
//		ghosts[countGhosts].setPosition(row, col);
//		countGhosts++;
//	}
//}

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
	if(checkIfTheSamePosition(pac.getNextPosition(), ghosts[0].getNextPosition()) || checkIfTheSamePosition(pac.getNextPosition(), ghosts[1].getNextPosition()))
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
			if ((dir = pac.getDirection(key)) != -1)
				pac.setDirection(dir);
		}
		
		pac.move();
		pointsAndLives[1].draw(pac.getPoints()); //draw points
		countPacMoves++;
		
		
		if (countPacMoves == 2 && gameIsOn)
		{
			ghosts[0].move(pac.getNextPosition());
			ghosts[1].move(pac.getNextPosition());
			countPacMoves = 0;
		}
	
		Sleep(400);
	} while (key != ESC && gameIsOn);
	clear_screen();
	if (!gameIsOn)
	{
		printGameOver();
		Sleep(3000);
		clear_screen();
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
	pac.getNextPosition().draw('@');
	updateBoard(pac.getNextPosition());
	ghosts[0].getNextPosition().draw('$');
	ghosts[1].getNextPosition().draw('$');
}

void ThePacmanGame::ghostAtePacman()
{
	pac.setLives(); 
	if (pac.getLives() != 0)
	{
		setBoardBeforeStrike(ghosts[0].getNextPosition());
		setBoardBeforeStrike(ghosts[1].getNextPosition());
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

