/*
	Board Class File
*/

#include "Board.h";

// Constructors and Destructors
Board::Board() {
	boardCollumns = 0;
	boardCollumns = 0;
	boardCurrentRow = 0;
}
Board::Board(int Row, int Collumn) {
	boardRows = Row;
	boardCollumns = Collumn;
	boardCurrentRow = 0;

	/*
	vector<string> boardPlayerMoves;
	vector<string> boardPlayerClues;
	int boardRows;
	int boardCollumns;
	int boardCurrentRow;*/

};
Board::~Board() {};

// Functions
void Board::displayBoard() {
	// Print out the part  of the hidden code
	// Print Top
	cout << "\n  ." << string(boardCollumns * 6 + 15, '-') << ".\n";
	cout << "  |";
	for (int i = 0; i < boardCollumns; i++) {
		cout << " .---.";
	}
	cout << string(15, ' ') << "|\n";
	// Print the middle
	cout << "  |";
	for (int i = 0; i < boardCollumns; i++) {
		cout << " |   |";
	}
	cout << "  Hidden Code" << "  " << "|\n";
	// Print Bottom
	cout << "  |";
	for (int i = 0; i < boardCollumns; i++) {
		cout << " *---*";
	}
	cout << string(15, ' ') << "|\n";

	// Generating the base game Board
	// Declaring some variables fo the function
	string Boxes;
	string boxTop;
	string boxMid;
	string boxBot;
	int lastMovePerRow;
	int boardVectorIter = 0;
	int hintVectorIter = 0;
	int noClueCounter;
	// Loop for the amount of rows
	for (int row = 0; row < boardCurrentRow; row++) {
		boxTop = "  |";
		boxMid = "  |";
		boxBot = "  |";
		lastMovePerRow = boardVectorIter + boardCollumns;
		//asdaate a nice row
		while (boardVectorIter < lastMovePerRow) {
			boxTop += " .---.";
			boxMid += " | ";
			boxMid += boardPlayerMoves[boardVectorIter];
			boxMid += " |";
			boxBot += " *---*";
			boardVectorIter++;
		}

		boxTop += string(15,' ')+ "|";
		boxMid += "  ";
		boxBot += string(15,' ') +"|";
		// Print Clue
		// O for correct | ? for somewhat | x as blank
		noClueCounter = 0;
		while (hintVectorIter < lastMovePerRow) {
			if (boardPlayerClues[hintVectorIter] != 'x') {
				boxMid += boardPlayerClues[hintVectorIter];
				boxMid += " ";
			}
			else {
				noClueCounter++;
			}
			hintVectorIter++;
		}
		// Fill in if no clues
		for (int i = 0; i < noClueCounter; i++) {
			boxMid += "  ";
		}
		boxMid += string(15-(boardCollumns*2+2), ' ') + "|";

		Boxes = boxTop + "\n" + boxMid + "\n" + boxBot + "\n" + Boxes;
	}
	Boxes = "  |" + string(boardCollumns*6 + 15, '_') + "|\n" + Boxes + "  *" + string(boardCollumns*6 + 15, '-') + "*\n";
	cout << Boxes;
};

void Board::resetGame() {
	// Empty the vectors so a new game can be started
	boardPlayerMoves.clear();
	boardPlayerClues.clear();
	boardCurrentRow = 0;
};

void Board::addToMoves(string& moves) {
	//Loop throught the list and add it to the vector
	for (int i = 0; i < moves.size(); i++) {
		boardPlayerMoves.push_back(moves.at(i));
	}
};

void Board::addToClues(string& clues) {
	//Loop throught the list and add it to the vector
	for (int i = 0; i < clues.size(); i++) {
		boardPlayerClues.push_back(clues.at(i));
	}
};

int Board::getCollumns() {
	return boardCollumns;
}

int Board::getRows() {
	return boardRows;
}

int Board::getCurrentRow() {
	return boardCurrentRow;
}

void Board::updateCurrentRow(int value) {
	boardCurrentRow = value;
}