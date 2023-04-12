#include <windows.h>
#include <iostream>
using namespace std;

#include "ThePacmanGame.h"
#include "_board.h"

int main() {
	ThePacmanGame game;
	game.setBoard(board_example);
	game.init();
	game.run();
}