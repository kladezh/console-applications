#include <iostream>
#include "game.h"

int main() {
	srand(time(NULL));

	Game game;

	game.setPlayerName();
	game.play();
	game.printResult();

	return 0;
}
