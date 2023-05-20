#ifndef _MENU_H_
#define _MENU_H_
#include <cstdlib>
#include <windows.h>
#include <string>
#include <vector>

#define NUM_OF_SCREENS 3


enum {START_GAME = 1, INSTRUCTIONS = 8, EXIT = 9};
enum {YES = 'Y', NO = 'N' };
class Menu {
	bool default_mode;
public:
	void print();
	void userChoseDefaultMode(bool color);
	bool has_ending(std::string const& fullString, std::string const& ending);
	void listdir(const std::string& path, std::vector<std::string>& files, const std::string& suffix);
	void userChoseScreen(bool color);
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

