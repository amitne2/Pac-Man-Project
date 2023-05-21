#include "Menu.h"
#include "ThePacmanGame.h"

#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

//This function print the menu option 
//1-for start new game
//8-for instructions and keys
//9- for exit
//The function runs until the user enters 9 to exit from the game
void Menu::print() {
	
	int choice;
	bool default_mode;
	char game_level;
	srand(time(NULL)); //Added for random
	printOptions(); 
	cin >> choice;
	hideCursor();
	while (choice != EXIT)
	{
		switch (choice)
		{
		case START_GAME: 
			manageGame();

			break;
		case INSTRUCTIONS: 
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
}
//This function calls the function that start the game considering the user's choice
void Menu::manageGame()
{
	bool color = checkIfColored();
	
	if (isDefaultMode())
		userChoseDefaultMode(color);
	else
		userChoseScreen(color);
}
//This function asks the user if he wants to play with specific screen or in default mode
//checks the answer is valid
//return the true if the user wants dafult mode
//return false if wants specific screen
bool Menu::isDefaultMode() const
{
	char c;
	bool validAnswer = false,res;
	cout << "Would you like to select a screen? Please choose Y/N" << endl;
	cout << "Note that chosing 'N' means playing the default screens." << endl;

	while (!validAnswer)
	{
		cin >> c;
		c = toupper(c);
		switch (c)
		{
		case YES:
			res = false;
			validAnswer = true;
			break;
		case NO:
			res = true;
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
//The function return true of the fullstring ending with the string endting we got
//ekse return false
bool Menu::has_ending(string const& fullString, string const& ending) const
{
	if (fullString.length() >= ending.length()) {
		return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
	}
	else {
		return false;
	}
}
//This function gets vector with all files names in the directory 
//and remove all files except for the game screens (pacman_*.screen).
void Menu::listdir(const string& path, vector<string>& files, const string& suffix) const
{
	for (const auto& entry : fs::directory_iterator(path)) {
		string entryStr = entry.path().string();

		if (has_ending(entryStr, suffix)) {
			files.push_back(entryStr);
		}
	}
}
//This function handles when the user selects default mode (without specific screen)
//run on the 3 screen (stop after 3 screen or if the user lost the game before)
void Menu::userChoseDefaultMode(bool color)
{
	ThePacmanGame game(color);
	bool gameIsOn = true;
	int countScreens = 0;
	vector<string> files;
	listdir(".", files, "screen");
	sort(files.begin(), files.end());
	
	for (const auto& path: files) 
	{
		game.start(path);
		if (game.getPacmanLives() == 0)
			gameIsOn = false;
		else if (countScreens != NUM_OF_SCREENS) //if countScreens=NUM_OF_SCREENS, you're on the last screen, no need to prepare for another game
		{
			game.prepareGameForNextScreen(); 
			printChangingScreenMessage();
		}
		
		countScreens++;
		if (!gameIsOn)
			break;
	}
	gameResult(game.getPacmanLives(), color);
}
//This function prints the message according to user result's 
//prints game over when lives is 0
//else prints winning message
void Menu::gameResult(int lives, bool color) const
{
	if (lives == 0)
		printGameOver(color);
	else
		printWinningMessage(color);

	Sleep(1000);
	_getch();
	clear_screen();
}

//This function handles the mode that the user selects specific screen
void Menu::userChoseScreen(bool color)
{
	ThePacmanGame game(color);
	string new_name;
	clear_screen();
	cout << "Please enter the name of the screen you would like to upload:" << endl;
	cin >> new_name;


	std::ifstream screenFile(new_name);

	if (!screenFile.is_open() || !screenFile.good())
	{
		cout << "There is no such file!" << endl;
		clear_screen();
	}
	else
	{
		//game.setScreenMode(false);
		game.start(new_name);
		gameResult(game.getPacmanLives(), color);
		screenFile.close();
	}
}
//This function print changing Screen Message.
void Menu::printChangingScreenMessage() const
{
	clear_screen();
	cout << "	    	                  _         _       _   _                 " << endl;
	cout << "                                 | |       | |     | | (_)" << endl;
	cout << "   ___ ___  _ __   __ _ _ __ __ _| |_ _   _| | __ _| |_ _  ___  _ __  ___" << endl;
	cout << "  / __/ _ \\| '_ \\ / _` | '__/ _` | __| | | | |/ _` | __| |/ _ \\| '_ \\/ __|" << endl;
	cout << " | (_ |(_) | | | | (_| | | | (_| | |_| |_| | | (_| | |_| | (_) | | | \\ __\\" << endl;
	cout << "  \\___\\___/|_| |_|\\__, |_|  \\__,_|\\__|\\__,_|_|\\__,_|\\__|_|\\___/|_| |_|___/" << endl;
	cout << "                   __/ |" << endl;
	cout << "                 |___ /" << endl;
	cout << "#Press any key on your keyboard to move to the next screen in the game." << endl;
	Sleep(1000);
	_getch();
	clear_screen();
}

//This function prints the menu options 
void Menu::printOptions() const
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
void Menu::printInstructions() const
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
bool Menu::checkIfColored() const
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
		case YES:
			res = true;
			validAnswer = true;
			break;
		case NO:
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


//This function prints the GAME OVER message.
void Menu::printGameOver(bool color) const
{
	clear_screen();
	if (color)
		setTextColor(LIGHTRED);
	cout << "######       ###    ##     ## ########     #######  ##     ## ######## ########   ####  ####" << endl;
	cout << "##    ##    ## ##   ###   ### ##          ##     ## ##     ## ##       ##     ##  ####  ####" << endl;
	cout << "##         ##   ##  #### #### ##          ##     ## ##     ## ##       ##     ##  ####  ####" << endl;
	cout << "##   #### ##     ## ## ### ## ######      ##     ## ##     ## ######   ########    ##    ##" << endl;
	cout << "##    ##  ######### ##     ## ##          ##     ##  ##   ##  ##       ##   ## " << endl;
	cout << "##    ##  ##     ## ##     ## ##          ##     ##   ## ##   ##       ##    ##   ####  ####" << endl;
	cout << "######    ##     ## ##     ## ########     #######     ###    ######## ##     ##  ####  ####" << endl;
	setTextColor(WHITE);

	cout << endl << "# Press any key on your keyboard to go back to the menu." << endl;
}

//This function prints the WINNER message.
void Menu::printWinningMessage(bool color) const
{
	clear_screen();
	if (color)
		setTextColor(MAGENTA);
	cout << "##      ## #### ##    ## ##    ## ######## ########  #### ####" << endl;
	cout << "##  ##  ##  ##  ###   ## ###   ## ##       ##     ## #### ####" << endl;
	cout << "##  ##  ##  ##  ####  ## ####  ## ##       ##     ## #### ####" << endl;
	cout << "##  ##  ##  ##  ## ## ## ## ## ## ######   ########   ##   ##" << endl;
	cout << "##  ##  ##  ##  ##  #### ##  #### ##       ##   ##" << endl;
	cout << "##  ##  ##  ##  ##   ### ##   ### ##       ##    ##  #### ####" << endl;
	cout << "###   ###  #### ##    ## ##    ## ######## ##     ## #### ####" << endl;
	setTextColor(WHITE);
	cout << endl << "# Press any key on your keyboard to go back to the menu." << endl;
}

