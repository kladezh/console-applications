#include <iostream>
#include <cassert>
#include <array>

#define COUNT_OF_ATTEMPTS 6

size_t range_rand(size_t left, size_t right) {
	return left + rand() % (right - left + 1);
}

class Game {
private:
	std::string aplhabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	const std::array<std::string, 10> word_list{
		"BRANCH", "CORRICULUM", "INTENTION", "SERVANT", "ACCIDENT",
		"THREAT", "COURAGE", "ARRANGEMENT", "QUARREL", "AMOUNT"
	};

private:
	std::string taked_word;
	std::string interact_word;
	int count_attempts;
	bool result;

	void printInteractWord();
	void takeRandWord();
	bool hasBeenSuchLetter(const char letter);
	bool isLetter(const char letter);
	void guessing();

public:
	Game() : taked_word(""), interact_word(""), count_attempts(COUNT_OF_ATTEMPTS), result(false)
	{
	}

	void startGame();
	void printResultGame();

};

int main() {

	Game game;

	game.startGame();
	game.printResultGame();

	return 0;
}

void Game::printInteractWord() {
	std::cout << "\nThe word: ";
	for (auto& let : interact_word) {
		std::cout << let << " ";
	}
	std::cout << "\n\n";
}


void Game::takeRandWord() {
	srand(time(NULL));

	taked_word = word_list[range_rand(0, word_list.size() - 1)];
	for (auto& let : taked_word) {
		interact_word.push_back('_');
	}
}

bool Game::hasBeenSuchLetter(const char letter) {
	std::string::size_type ind;
	if ((ind = aplhabet.find(letter)) != std::string::npos) {
		aplhabet[ind] = '0';
		return false;
	}
	else {
		return true;
	}
}

bool Game::isLetter(const char letter) {
	std::string::size_type ind, rind;

	if ((ind = taked_word.find(letter)) != std::string::npos) {
		interact_word[ind] = letter;
		if ((rind = taked_word.rfind(letter)) != ind) {
			interact_word[rind] = letter;
		}
		return true;
	}
	else {
		return false;
	}
}

void Game::guessing() {
	char let;

	while (interact_word != taked_word && count_attempts > 0) {
		printInteractWord();
		std::cout << "Guess the letter: ";
		std::cin >> let;
		let = toupper(let);

		if (hasBeenSuchLetter(let)) {
			std::cout << "You've already gotten this letter before...\n";
			continue;
		}

		if (isLetter(let)) {
			std::cout << "Great!\n";
		}
		else {
			count_attempts--;
			std::cout << "There's no such letter! Your attempts: " << count_attempts << '\n';
		}
	}

	result = (interact_word == taked_word);
}

void Game::startGame() {
	takeRandWord();
	guessing();
}

void Game::printResultGame() {
	if (result) {
		std::cout << "\nYou win!";
	}
	else {
		std::cout << "\nYou lose";
	}
	printInteractWord();
}
