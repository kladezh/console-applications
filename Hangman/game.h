#pragma once

#include <iostream>
#include <cassert>
#include <array>

#include "functions.h"

class Game {
private:
	std::string aplhabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	const std::array<std::string, 10> word_list{
		"BRANCH", "CORRICULUM", "INTENTION", "SERVANT", "ACCIDENT",
		"THREAT", "COURAGE", "ARRANGEMENT", "QUARREL", "AMOUNT"
	};

private:
	static const int DEFAULT_ATTEMPTS_COUNT = 6;

	std::string taked_word;
	std::string interact_word;
	int attempts_count;
	bool result;

	void printInteractWord();
	void takeRandWord();
	bool hasBeenSuchLetter(const char letter);
	bool isLetter(const char letter);
	void guessing();

public:
	Game() : taked_word(""), interact_word(""), attempts_count(DEFAULT_ATTEMPTS_COUNT), result(false)
	{
	}

	void startGame();
	void printResultGame();

};

