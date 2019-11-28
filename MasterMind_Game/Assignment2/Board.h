#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Board {
private:
	// Variable Definitions
	vector<char> boardPlayerMoves;
	vector<char> boardPlayerClues;
	int boardRows;
	int boardCollumns;
	int boardCurrentRow;

public:
	// Constructors
	Board();
	Board(int Row, int Collumn);
	~Board();

	// Functions Definitions
	void displayBoard();
	void resetGame();
	void addToMoves(string& moves);
	void addToClues(string& clues);
	int getCollumns();
	int getRows();
	int getCurrentRow();
	void updateCurrentRow(int value);
};

#endif