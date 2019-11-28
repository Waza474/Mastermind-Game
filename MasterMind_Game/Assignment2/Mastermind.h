#ifndef MASTERMIND_H
#define MASTERMIND_H

// Include Statements
#include <iostream>;
#include <fstream>;
#include <string>;
#include <ctime>;
#include "Player.h";
#include "Board.h";

using namespace std;

// Variable Definitions
string generatedCode;
string codeForClues;
int cluesRemaining;
Player codeBreaker;
Board codeMaster;
float gameScore;
int difficultyModifier;
float winStreakModifier;
int gameDifficulty;
int currentDifficultyStreak;
string givenClues;

vector<char> userGuess;
vector<char> usersHints;

// Function Definitions
void displayHowTo();
void userLogin();
void displayTopBar();
string generateCode(int maxNumber, int codeLength);
string checkCode(string& userCode, string& gameCode);
void displayStats();
void giveHint();
void saveToFile();
void loadFromFile();
void checkWinStreak();
void newBoard();

string getUserString(string question);
int getUserNumber(string question);

#endif