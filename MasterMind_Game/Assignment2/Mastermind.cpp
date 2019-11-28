#include "Mastermind.h"

int main() {
	// Start by displaying how to text.
	displayHowTo();
	system("CLS");
	// Get user info and difficulty
	userLogin();

	winStreakModifier = 1.0;

	// Main Game Loops
	string userInput = "Play";
	displayTopBar();

	// Generate a Code
	generatedCode = generateCode(9, codeMaster.getCollumns());
	// Display the Board
	codeMaster.displayBoard();
	// Get input and validate
	bool stopPlay = false;
	//cout << "\n  Valid inputs include a " << codeMaster.getCollumns() << " code, or one of the following letters..";
	while (!stopPlay ){//&& codeMaster.getCurrentRow() != codeMaster.getRows()) {
		// Get the user input
		cout << "\n  Code Elements: 1 2 3 4 5 6 7 8 9";
		cout << "\n  Other inputs: C (clue)  H (help)  Q (quit)  X (skip)  S (save)  L (load)";
		cout << "\n  Enter a code or another valid input: ";
		cin >> userInput;
		if (userInput.length() == codeMaster.getCollumns()) {
			// Is the code the correct code?
			if (userInput == generatedCode) {
				// you win, update score appropriately
				string correct(codeMaster.getCollumns(), 'o');
				codeMaster.addToMoves(userInput);
				codeMaster.addToClues(correct);
				codeMaster.updateCurrentRow(codeMaster.getCurrentRow() + 1);
				system("CLS");
				displayTopBar();
				codeMaster.displayBoard();
				cout << "\n  Nice work captain. you have successfully defused the bomb.\n\n";
				// show stats and continue next game (check win streak)
				codeBreaker.updateGames(codeBreaker.getGames() + 1);
				codeBreaker.updateWins(codeBreaker.getWins() + 1);
				codeBreaker.updateWinStreak(true);
				currentDifficultyStreak += 1;
				// updates player score
				winStreakModifier += 0.1;
				gameScore = (codeMaster.getRows() - codeMaster.getCurrentRow()) * difficultyModifier * winStreakModifier;
				codeBreaker.updateScore(gameScore + codeBreaker.getScore());
				// Show the stats
				displayStats();
				// check win streak and advance if required
				checkWinStreak();
				// start new board
				cout << "\n  Another bomb has been found and is ready to be defused.\n  ";
				system("pause");
				system("CLS");
				newBoard();
				displayTopBar();
				codeMaster.displayBoard();
			}
			// not correct
			else {
				// is it the last code?
				string feedback = checkCode(userInput, generatedCode);
				cout << feedback;
				codeMaster.addToMoves(userInput);
				codeMaster.addToClues(feedback);
				system("CLS");
				codeMaster.updateCurrentRow(codeMaster.getCurrentRow() + 1);
				displayTopBar();
				codeMaster.displayBoard();
				if (codeMaster.getCurrentRow() >= codeMaster.getRows()) {
					// yes? reveal the code, update win and loss streak and more and continue (check if demote required)
					cout << "\n  Bad luck captain, you have failed to defuse the bomb.\n  Our system found the code to be: "<< generatedCode <<" but it was too late.\n\n";
					// update the players stats, their score does not change
					codeBreaker.updateGames(codeBreaker.getGames() + 1);
					codeBreaker.updateWinStreak(false);
					if (currentDifficultyStreak > 0) { currentDifficultyStreak = 0; }
					else { currentDifficultyStreak--; }
					gameScore = 0;
					// Show stats, check loss streak, prepare next game on next
					displayStats();
					checkWinStreak();
					cout << "\n  You may have failed this bomb.\n  But BAM crew are still out there with more bombs.\n  ";
					system("pause");
					system("CLS");
					newBoard();
					displayTopBar();
					codeMaster.displayBoard();
				}
				// no? then compute the hint and go back to loop
			}
		}
		// Reveal a random number
		else if (userInput == "C" || userInput == "c") {
			giveHint();
		}
		else if (userInput == "H" || userInput == "h") {
			system("CLS");
			displayHowTo();
			system("CLS");
			displayTopBar();
			codeMaster.displayBoard();
			if (givenClues.length() != 0) { cout << "\n  Clues: " << givenClues << "\n"; }
		}
		else if (userInput == "Q" || userInput == "q") {
			while (userInput != "y" && userInput != "n" && userInput != "Y"&& userInput != "N") {
				cout << "\n  NOTE: If have not saved your stats, you can do so.\n  Are you sure you want to quit now captain? (Y/N) ";
				cin >> userInput;
			}
			if (userInput == "y" || userInput == "Y") {
				cout << "\n\n  Thank you Captain, BAM must be stopped.\n\n\n\t\t  BOMB DEFUSER HAS GONE OFFLINE\n\n";
				stopPlay = true;
			}
		}
		else if (userInput == "X" || userInput == "x") {
			// Confirm their choice
			bool confirmation = false;
			cin.ignore();
			while (confirmation == false) {
				userInput = getUserString("\n  Are you sure you want to skip this bomb? (Y/N) ");

				if (userInput == "Y" || userInput == "y") {
					if (gameDifficulty == 1) { cluesRemaining = 3; }
					else if (gameDifficulty == 2) { cluesRemaining = 4; }
					else if (gameDifficulty == 3) { cluesRemaining = 5; }
					// Set any variables for the next game
					codeBreaker.updateWinStreak(false);
					currentDifficultyStreak--;
					codeBreaker.updateGames(codeBreaker.getWins() + 1);
					generatedCode = generateCode(9, codeMaster.getCollumns());
					// Display score
					displayStats();
					cout << "\n  Bomb has been skipped and counter as a loss. Continue for a new bomb.\n\n  ";
					system("pause");
					confirmation = true;
					system("CLS");
					displayTopBar();
					codeMaster.displayBoard();
					if (givenClues.length() != 0) { cout << "\n  Clues: " << givenClues << "\n"; }
				}
				else if (userInput == "N" || userInput == "n") { confirmation = true; }
			}
		}
		else if (userInput == "S" || userInput == "s") {
		cout << "\n";
		system("cls");
		displayTopBar();
		displayStats();
			while (userInput != "y" && userInput != "n" && userInput != "Y"&& userInput != "N") {
				cout << "\n  NOTE: Saving will not save current bomb progress!\n  Do you want to save this data? (Y/N) ";
				cin >> userInput;
			}
			if (userInput == "y" || userInput == "Y") {
				saveToFile();
				cout << "\n  ";
				system("pause");
				system("CLS");
				displayTopBar();
				codeMaster.displayBoard();
			}
			else {
				system("cls");
				displayTopBar();
				codeMaster.displayBoard();
			}
		}
		else if (userInput == "L" || userInput == "l") {
			system("cls");
			displayTopBar();
			while (userInput != "y" && userInput != "n" && userInput != "Y"&& userInput != "N") {
				cout << "\n  NOTE: Loading will wipe current bomb progress!\n  Do you want to load saved data? (Y/N) ";
				cin >> userInput;
			}
			if (userInput == "y" || userInput == "Y") {
				loadFromFile();
				cout << endl;
				displayStats();
				cout << "\n  ";
				system("pause");
				// Start a new game with the new stuff
				system("cls");
				displayTopBar();
				codeMaster.displayBoard();
			}
			else {
				system("cls");
				displayTopBar();
				codeMaster.displayBoard();
			}
		}
		else {
			cout << "\n Invalid input. Enter a valid code or special character.\n";
		}
	}
	cout << "\n  ";
	system("pause");
	return 0;
}

// Function to display the how to text
void displayHowTo() {
	system("CLS");
	// Declare any required varaibles including filestream
	string line;
	ifstream howToFile;
	howToFile.open("SCPFHowTo.txt");
	// Ensure that it is open
	if (howToFile.is_open()) {
		while (getline(howToFile, line)) {
			cout << line << endl;
		}
	}
	else {
		cout << "The SCPFHowTo.txt file does not exist";
	}
	// let the user read the information and finish
	howToFile.close();
	cout << "\n\t";
	system("pause");
}

void userLogin() {
	// Declare any local variables that might be needed
	string tempString;
	gameDifficulty = 0;
	// Display the Top graphic and get user name
	displayTopBar();
	tempString = getUserString("\n  Welcome to the Super City Police Force central system.\n  Please enter your name to begin: ");
	codeBreaker = Player(tempString);
	cout << "\n\n  Welcome back Captain " << tempString <<".";
	// Get the game difficulty
	cout << "\n\n\n  Please choose a villain you will be pursuing today...\n";
	cout << "  [1] Blast Boy = standard: 4 columns x 10 rows\n  [2] Amateur Atom = tricky : 5 columns x 12 rows - AND DUPLICATES!\n  [3] Mastermind = hard : 6 columns x 14 rows\n\n";
	// Ensuring a valid difficulty is entered
	while (gameDifficulty == 0) {
		tempString = getUserString("  Enter one of the numbers above: ");
		if (tempString == "1") {
			gameDifficulty = 1;
			difficultyModifier = 1;
			cluesRemaining = 3;
			codeMaster = Board(10, 4);
			cout << "\n  You have selected: [1] Blast Boy";
		}
		else if (tempString == "2") {
			gameDifficulty = 2;
			difficultyModifier = 2;
			codeMaster = Board(12, 5);
			cluesRemaining = 4;
			cout << "\n  You have selected: [2] Amatuer Atom";
		}
		else if (tempString == "3") {
			gameDifficulty = 3;
			difficultyModifier = 3;
			codeMaster = Board(14, 6);
			cluesRemaining = 5;
			cout << "\n  You have selected: [3] Mastermind";
		}
		else {
			cout << "  Invalid input. Try again.\n\n";
		}
	}
	// Setting any other Variables to their start position
	gameScore = 0;
	winStreakModifier = 0;

	cout << "\n\n\n  Thank you for using Super City Police Force's central system,\n  best of luck out there Captain...";

	// Pause and continue
	cout << "\n\n\t";
	system("pause");
	system("CLS");
}

void displayTopBar() {
	cout << "+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x\n                  Mastermind : Super City Police Force\n+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x+x\n";
}

string generateCode(int maxNumber, int codeLength) {
	// Any Variable Definitions
	string tempCode = ""; // Makes the code, if any, empty
	int rollResult;
	srand(unsigned(time(NULL)));
	// loop enought times to fill a code of said length
	while (tempCode.length() < codeLength) {
		// Generate random code
		rollResult = rand() % maxNumber + 1;
		// Uses find but as a boolean
		if (gameDifficulty != 2) {
			if (tempCode.find(to_string(rollResult)) == string::npos) {
				tempCode += to_string(rollResult);
			}
		}
		else { tempCode += to_string(rollResult); }
	}
	return tempCode;
}

string checkCode(string& userCode, string& gameCode) {
	// Does have time complexity of O(n^2) but gets the job done of looping through the list for each element
	// and checking if there exist the letter in the other code
	// note: both should be same length
	string partA, partB;
	for (int i = 0; i < userCode.length(); i++) {
		for (int j = 0; j < gameCode.length(); j++) {
			if (userCode.at(i) == gameCode.at(j)) {
				if (i == j) { partA += "o"; }
				else { partB += "?"; }
			}
		}
	}
	return partA + partB + string(userCode.length()-(partA+partB).length(),'x');
}

void displayStats() {
	// Function to display everything player
	string wrapper;
	if (codeBreaker.getName().length() > 16) {
		wrapper = string(26 + codeBreaker.getName().length(), '~');
	}
	else {
		wrapper = string(42, '~');
	}
	cout << "  " << wrapper << endl;
	cout << "   Name:\t\t  " << codeBreaker.getName() << endl;
	string target[] = {"[1] Blast Boy","[2] Amateur Atom","[3] Mastermind"};
	cout << "   Current Target:\t  " << target[gameDifficulty] << endl;
	cout << "   Bombs Attempted:\t  " << codeBreaker.getGames() << endl;
	cout << "   Successful Defuses:\t  " << codeBreaker.getWins() << endl;
	cout << "   Current Defuse Streak: " << codeBreaker.getWinStreak() << endl;
	cout << "   Last Game Score:\t  " << gameScore << endl;
	cout << "   Total Score:\t\t  " << codeBreaker.getScore() << endl;
	cout << "  " << wrapper << endl;
}

void giveHint() {
	if (cluesRemaining != 0) {
		// Find A random number not given yet
		int rollResult = 9999;
		srand(unsigned(time(NULL)));
		bool goodVal = false;
		while (goodVal == false) {
			if (givenClues.find(to_string(rollResult)) == string::npos) { goodVal = true; }
			rollResult = rand() % 9 + 1;
		}
		givenClues += to_string(rollResult) + " ";
		cluesRemaining--;
		cout << "\n New Clue: ";
	}
	else { cout << "\n  No clue remaining, here are the previous clues: "; }
	// Display to user
	cout << givenClues << "\n";
}

void saveToFile() {
	bool saveToFile = true;
	string overwriteChoice = "blank";
	// Check if there is an existing save that will be wiped
	ifstream checkFile;
	checkFile.open("SCPFsave.txt");
	if (checkFile.is_open()) {
		while (overwriteChoice != "y" && overwriteChoice != "n" && overwriteChoice != "Y"&& overwriteChoice != "N") {
			cout << "\n  A save file already exist. Do you want to overwrite the save? (Y/N)";
			cin >> overwriteChoice;
		}
		if (overwriteChoice == "n" || overwriteChoice == "N") {
			saveToFile = false;
		}
	}
	checkFile.close();
	// Creating any local variables that are required
	if (saveToFile) {
		ofstream fileToWrite("SCPFsave.txt");
		fileToWrite << codeBreaker.getName() << endl;
		fileToWrite << gameDifficulty << endl;
		fileToWrite << codeBreaker.getGames() << endl;
		fileToWrite << codeBreaker.getWins() << endl;
		fileToWrite << codeBreaker.getWinStreak() << endl;
		fileToWrite << gameScore << endl;
		fileToWrite << codeBreaker.getScore() << endl;

		cout << "  File successfully saved\n";
		fileToWrite.close();
	}
}

void loadFromFile() {
	// Assigning any required variables
	int i = 0;
	ifstream saveFile;
	string line;
	saveFile.open("SCPFsave.txt");
	// saving the appropriate data
	if (saveFile.is_open()) {
		while (getline(saveFile, line)) {
			if (i == 0) { codeBreaker.updateName(line); }
			else if (i == 1) { gameDifficulty = stoi(line); }
			else if (i == 2) { codeBreaker.updateGames(stoi(line)); }
			else if (i == 3) { codeBreaker.updateWins(stoi(line)); }
			else if (i == 4) {
				int winStreakTemp = stoi(line);
				if (codeBreaker.getWinStreak() > 0){ codeBreaker.updateWinStreak(false); }
				while (winStreakTemp != 0) {
					if (winStreakTemp < 0) { codeBreaker.updateWinStreak(false); winStreakTemp++; }
					else { codeBreaker.updateWinStreak(true); winStreakTemp--; }
				}
			}
			else if (i == 5) { gameScore = stof(line); }
			else if (i == 6) { codeBreaker.updateScore(stof(line)); }
			i++;
		}
		newBoard();
		cout << "\n  File successfully loaded\n";
	}
	else {
		cout << "\n  Save file \"SCPFsave.txt\" does not exist.";
	}
	saveFile.close();
}

void checkWinStreak() {
	bool confirmation = false;
	cin.ignore();
	string promoteInput = "blank:";
	// Is it a win streak on that diffuculty
	if (currentDifficultyStreak >= 5) {
		while (!confirmation) {
			promoteInput = getUserString("\n  You have defused 5 of this villians bombs...\n  Would you like to move on to the next villian? (Y/N)  ");
			if (promoteInput == "Y" || promoteInput == "y") {
				if (gameDifficulty == 1) {
					gameDifficulty = 2;
					difficultyModifier = 2;
					codeMaster = Board(12, 5);
					cluesRemaining = 4;
					cout << "\n  You have beem promoted, new target: [2] Amatuer Atom";
					currentDifficultyStreak = 0;
					confirmation = true;
				}
				else if (gameDifficulty == 2) {
					gameDifficulty = 3;
					difficultyModifier = 3;
					codeMaster = Board(14, 6);
					cluesRemaining = 5;
					cout << "\n  You have beem promoted, new target:: [3] Mastermind";
					currentDifficultyStreak = 0;
					confirmation = true;
				}
			}
			else if (promoteInput == "N" || promoteInput == "n") { confirmation = true; }
		}
	}
	// is it a losing streak
	else if (currentDifficultyStreak <= -4) {
		while (!confirmation) {
			promoteInput = getUserString("\n  You failed to defuse the last 5 bombs...\n  Would you like to go to the easier villian? (Y/N) ");
			if (promoteInput == "Y" || promoteInput == "y") {
				if (gameDifficulty == 2) {
					gameDifficulty = 1;
					difficultyModifier = 1;
					codeMaster = Board(10, 4);
					cluesRemaining = 3;
					cout << "\n  You have beem demoted, new target: [1] Blast Boy";
					currentDifficultyStreak = 0;
					confirmation = true;
				}
				else if (gameDifficulty == 3) {
					gameDifficulty = 3;
					difficultyModifier = 3;
					codeMaster = Board(14, 6);
					cluesRemaining = 5;
					cout << "\n  You have beem demoted, new target: [2] Amateur Atom";
					currentDifficultyStreak = 0;
					confirmation = true;
				}
			}
			else if (promoteInput == "N" || promoteInput == "n") { confirmation = true; }
		}
	}
}

string getUserString(string question) {
	cout << question;
	string UserInput = "blank";
	getline(cin, UserInput);
	return UserInput;
}

int getUserNumber(string question) {
	int UserInput = 0;
	cout << question;
	cin.ignore();
	cin >> UserInput;
	return UserInput;
}

void newBoard() {
	if (gameDifficulty == 1) {
		difficultyModifier = 1;
		cluesRemaining = 3;
		codeMaster = Board(10, 4);
	}
	else if (gameDifficulty == 2) {
		difficultyModifier = 2;
		codeMaster = Board(12, 5);
		cluesRemaining = 4;
	}
	else if (gameDifficulty == 3) {
		difficultyModifier = 3;
		codeMaster = Board(14, 6);
		cluesRemaining = 5;
	}
	codeMaster.resetGame();
	generatedCode = generateCode(9, codeMaster.getCollumns());
}