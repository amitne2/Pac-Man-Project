#include "Menu.h"
#include "ThePacmanGame.h"
#include <cstdlib>
#include <windows.h>

using namespace std;


void Menu::print() {
	int choice;
	printOptions();
	cin >> choice;
	hideCursor();
	while (choice != 9)
	{
		switch (choice)
		{
		case 1:
			ThePacmanGame().start();
			break;
		case 8:
			cout << "FINISH";
			break;
		default:
			cout << "WRONG KEY! PLEASE CHOOSE AGAIN." << endl;
			break;
		}

		printOptions();
		cin >> choice;
	}

	exit(0);
}


void Menu::printOptions()
{
	cout << "*********************** WELCOME TO THE PACMAN GAME! ***********************" << endl;
	cout << "Please choose an option:" << endl << "(1) Start a new game" << endl;
	cout << "(8) Present instructions and keys" << endl << "(9) EXIT" << endl;
}