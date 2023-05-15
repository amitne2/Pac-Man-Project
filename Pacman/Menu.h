#ifndef _MENU_H_
#define _MENU_H_
#include <cstdlib>
#include <windows.h>
#include <string>

using std::string;

class Menu {
public:
	void print();
	string readFile();
	void printOptions();
	void printInstructions();
	bool checkIfColored();
};

#endif

