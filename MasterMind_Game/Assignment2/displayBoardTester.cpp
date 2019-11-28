#include <string>;
#include <sstream>;
#include <iostream>;
#include <fstream>;
#include <ctime>;
#include <vector>;

using namespace std;

/*
int main() {
	int boardCurrentRow = 2;
	int boardCollumns = 4;
	// Declaring some variables fo the function
	string Boxes;
	string boxTop;
	string boxMid;
	string boxBot;
	int LastMovePerRow = 0;
	vector<int> boardPlayerMoves{1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9};
	vector<string> boardPlayerClues{ "x","x","x","x","o","x","?","x" };
	int boardVectorIter = 0;
	int hintVectorIter = 0;
	int noClueCounter;
	// Loop for the amount of rows
	for (int row = 0; row < boardCurrentRow; row++) {
		
		// NEW UPDATE HERE `````````````````````````````````````
		boxTop = "  | ";
		boxMid = "  | ";
		boxBot = "  | ";
		LastMovePerRow = boardVectorIter + boardCollumns;
		// UPDATE ENDS````````````````````````````````````````````

		// Create a nice row
		while (boardVectorIter < LastMovePerRow) {
			boxTop += " .---.";
			boxMid += " | " + to_string(boardPlayerMoves[boardVectorIter]) + " |";
			boxBot += " *---*";

			boardVectorIter++;
		}

		// NEW UPDATE HERE```````````````````````````````````````````````````````
		boxTop += "               |";
		boxMid += "  ";
		boxBot += "               |";
		// Print Clue
		// O for correct | ? for somewhat | x as blank
		noClueCounter = 0;
		while (hintVectorIter < LastMovePerRow) {
			if (boardPlayerClues[hintVectorIter] != "x") {
				boxMid += boardPlayerClues[hintVectorIter] + " ";
			}
			else {
				noClueCounter++;
			}
			hintVectorIter++;
		}
		for (int i = 0; i < noClueCounter; i++) {
			boxMid += "  ";
		}
		// If No clue
		boxMid += "     |";
		// UPDATE ENDS```````````````````````````````````````````````

		Boxes = boxTop + "\n" + boxMid + "\n" + boxBot + "\n" + Boxes;
	}
	// NEW UPDATE HERE `````````````````````````````````````````````````````````
	Boxes = "  |________________________________________|\n" + Boxes + "  *----------------------------------------*\n";
	cout << Boxes;
	// END UPDATE ``````````````````````````````````````````````````````````````````
	// blah blah blah
	system("pause");
	return 0;
};*/