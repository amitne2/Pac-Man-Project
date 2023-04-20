#include "Menu.h"
#include "ThePacmanGame.h"
#include <cstdlib>
#include <windows.h>

using std:: cout;
using std:: cin;
using std:: endl;


void Menu::print() {
	char choice;
	printOptions();
	cin >> choice;
	hideCursor();
	while (choice != '9')
	{
		switch (choice)
		{
		case '1':
			ThePacmanGame().start();
			break;
		case '8':
			clear_screen();
			printInstructions();
			clear_screen();
			break;
		default:
			cout << "WRONG KEY! PLEASE CHOOSE AGAIN." << endl;
			Sleep(1000);
			clear_screen();
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

void Menu::printInstructions()
{
	cout << "Welcome to Pacman game!!!" << endl;
	cout << "Start the game by pressing the '1' key in menu screen. The start board will present on the screen with the pacman and 2 ghosts." << endl;
	cout << "# The Pacman can move around the board by using the arrow keys on your keyboard:" << endl;
	cout << "w or W - up" << endl;
	cout << "x or X - down" << endl;
	cout << "a or A- left" << endl;
	cout << "d or D- right" << endl;
	cout << "s or S- stay" << endl;
	cout << "# Eat all of the small dots 'BreadCrumbs' on the board while avoiding the two ghosts(Blinky and Pinky)" << endl;
	cout << "  that are chasing you. If a ghost touches Pacman, you lose a life." << endl;
	cout << "# Clear all the dots from the board to win in this game." << endl;
	cout << "# You have three lives to start with. You'll lose a life each time a ghost catches you." << endl;
	cout << "# The game ends when you run out of lives. Try to get the highest score you can!" << endl;
	cout << "# You can pause the game by pressing on 'ESC' key on your keyborad at any time," << endl;
	cout<< "   the board pauses until you press 'ESC' again." << endl;
	cout << "# Press any key on your keyboard to go back to the menu." << endl;
	_getch();
}
