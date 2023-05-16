#ifndef _MENU_H_
#define _MENU_H_
#include <cstdlib>
#include <windows.h>
#include <string>

#define NUM_OF_SCREENS 3
using std::string;
const string SCREEN_1 = "pacman_1.screen.txt";
const string SCREEN_2 = "pacman_2.screen.txt";
const string SCREEN_3 = "pacman_3.screen.txt";

class Menu {
	bool default_mode;
public:
	void print();
	void userChoseDefaultMode(bool color);
	void userChoseScreen(bool color);
	string getFileName(int ind);
	void manageGame();
	bool isDefaultMode();
	void printOptions();
	void printInstructions();
	bool checkIfColored();
	void printGameOver(bool color);
	void printWinningMessage(bool color);
	void printChangingScreenMessage();
	void gameResult(int lives, bool color); 
	~Menu() {}
};

#endif

