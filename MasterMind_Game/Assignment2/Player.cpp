/*
	Player Class File
*/

#include "Player.h";

// Constructors and Destructors
Player::Player() {
	playerName = "undefined";
	playerScore = 0;
	playerWins = 0;
	playerGames = 0;
	playerWinStreak = 0;
}
Player::Player(string name) {
	playerName = name;
	playerScore = 0;
	playerWins = 0;
	playerGames = 0;
	playerWinStreak = 0;
}

Player::~Player() {}

// Functions that simply return the private variables
string Player::getName() {
	return playerName;
}

float Player::getScore() {
	return playerScore;
};

int Player::getGames() {
	return playerGames;
};

int Player::getWins() {
	return playerWins;
};

int Player::getWinStreak() {
	return playerWinStreak;
};

// Functions to update values
void Player::updateName(string value) {
	playerName = value;
};

void Player::updateScore(float value) {
	playerScore = value;
};

void Player::updateWins(int value) {
	playerWins = value;
};

void Player::updateGames(int value) {
	playerGames = value;
};

void Player::updateWinStreak(bool victoryBool) {
	// if the input is true, that means the player had won
	if (victoryBool) {
		if (playerWinStreak >= 0) { playerWinStreak += 1; }
		else { playerWinStreak = 1; }
	}
	else {
		if (playerWinStreak > 0) {
			playerWinStreak = 0;
		}
		else {
			playerWinStreak--;
		}
	}
};


