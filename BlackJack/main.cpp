#include <iostream>
#include "blackjack.h"

int main() {
	srand(time(NULL));

	BlackJack game;
	game.startGame();

	std::cout << "Result is: " << game.getResultGame() << std::endl;

	return 0;
}
