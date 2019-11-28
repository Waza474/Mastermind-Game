#ifndef PLAYER_H
#define PLAYER_H

// Include Statements
#include <iostream>;
#include <string>;

using namespace std;

class Player {
private:
	// Variable Definitions
	string playerName;
	float playerScore;
	int playerWins;
	int playerGames;
	int playerWinStreak;


public:
	// Constructors
	Player();
	Player(string name);
	~Player();

	// Function Definitions
	string getName();
	float getScore();
	int getGames();
	int getWins();
	int getWinStreak();

	void updateName(string value);
	void updateScore(float value);
	void updateWins(int value);
	void updateGames(int value);
	void updateWinStreak(bool victoryBool);
};
#endif