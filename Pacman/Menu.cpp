#include "Menu.h"
#include "ThePacmanGame.h"

using std::cout;
using std::cin;
using std::endl;

//This function print the menu option 
//1-for start new game
//8-for instructions and keys
//9- for exit
//The function runs until the user enters 9 to exit from the game
void Menu::print() {
	string file_name;
	char choice;
	bool color;
	char game_level;
	srand(time(NULL)); //Added for random
	printOptions(); 
	cin >> choice;
	hideCursor();
	while (choice != '9')
	{
		switch (choice)
		{
		case '1': //start new game
			file_name = readFile();
			if(file_name != "NULL")
			{
				color = checkIfColored();
				ThePacmanGame(color).start(file_name);
			}
			break;
		case '8': //Instructions
			clear_screen();
			printInstructions();
			clear_screen();
			break;
		default: //wrong key
			cout << "WRONG KEY! PLEASE CHOOSE AGAIN." << endl;
			Sleep(1000);
			clear_screen();
			break;
		}

		printOptions();
		cin >> choice;
	}

	exit(0); //finish the game
}

string Menu::readFile()
{
	int num;
	string new_name;
	clear_screen();
	cout << "Please choose a number between 1-3 to upload a relevant screen:" << endl;
	cin >> num;
	//new_name = "C:\\Users\\amitn\\source\\CPP\\Pacman\\Pacman\\";
	new_name = "pacman_" + std::to_string(num) + ".screen";

	//std::ifstream screenFile(new_name, std::ios_base::in);
	std::ifstream screenFile(new_name);
	//screenFile.open(new_name, std::ios_base::in);
	if (!screenFile.is_open() || !screenFile.good())
	{
		cout << "There is no such file!" << endl;
		clear_screen();
		screenFile.close();
		return "NULL";
	}
	
	screenFile.close();
	return new_name;
}

//This function prints the menu options 
void Menu::printOptions()
{
	cout << " ########     ###     ######  ##     ##    ###    ##    ##"<< endl;
	cout << " ##     ##   ## ##   ##    ## ###   ###   ## ##   ###   ##" << endl;
	cout << " ##     ##  ##   ##  ##       #### ####  ##   ##  ####  ##" << endl;
	cout << " ########  ##     ## ##       ## ### ## ##     ## ## ## ##" << endl;
	cout << " ##        ######### ##       ##     ## ######### ##  ####" << endl;
	cout << " ##        ##     ## ##    ## ##     ## ##     ## ##   ###" << endl;
	cout << " ##        ##     ##  ######  ##     ## ##     ## ##    ##" << endl;
	cout << endl;
	cout << "************** WELCOME TO THE PACMAN GAME! ***************" << endl;
	cout << "Please choose an option:" << endl << "(1) Start a new game" << endl;
	cout << "(8) Present instructions and keys" << endl << "(9) EXIT" << endl;
	
}
//This function print the Instructions of the game
//The function stays on this screen until the user press on any key
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
//This function gets from user if he wants the game will be with/without colors
//If the user enter YES - update the variables to true 
//else - false
//print wrong key if the key invalid
bool Menu::checkIfColored()
{
	char colored;
	bool validAnswer = false, res;
	clear_screen();
	cout << "Would you like the game to be in color? Please enter Y/N" << endl;
	
	while (!validAnswer)
	{
		cin >> colored;
		colored = toupper(colored);
		switch (colored)
		{
		case 'Y':
			res = true;
			validAnswer = true;
			break;
		case 'N':
			res = false;
			validAnswer = true;
			break;
		default:
			cout << "WRONG KEY! PLEASE CHOOSE AGAIN - Y/N." << endl;
			Sleep(1000);
			break;
		}
	}

	return res;
}

////This function asks the player to choose the game level.
////Game level affects the ghosts behavior.
//char Menu::checkGameLevel()
//{
//	bool validAnswer = false;
//	char game_level;
//	cout << "Plase choose game level:" << endl;
//	cout << "a - Best" << endl;
//	cout << "b - Good" << endl;
//	cout << "c - Novice" << endl;
//	
//
//	while (!validAnswer)
//	{
//		cin >> game_level;
//		game_level = toupper(game_level);
//		switch (game_level)
//		{
//		case 'A':
//			validAnswer = true;
//			break;
//		case 'B':
//			validAnswer = true;
//			break;
//		case 'C':
//			validAnswer = true;
//			break;
//		default:
//			cout << "WRONG KEY! PLEASE CHOOSE AGAIN - A/B/C." << endl;
//			Sleep(1000);
//			break;
//		}
//	}
//	
//	return game_level;
//}