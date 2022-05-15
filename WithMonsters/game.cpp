#include "game.h"

void Game::setPlayerName() {
	std::string name;

	std::cout << "Enter your name: ";
	std::cin >> name;
	std::cout << "Welcome, " + name << "\n";

	player.setName(name);
}

void Game::monsterAttack() {
	player.reduceHealth(monster.getCountOfStrength());
	std::cout << "The " << monster.getName() << " hit you for " << monster.getCountOfStrength() << " damage.";
	std::cout << "  Your Health = " << player.getCountOfHealth() << ".\n";
}

void Game::playerAttack() {
	monster.reduceHealth(player.getCountOfStrength());
	std::cout << "You hit the " << monster.getName() << " for " << player.getCountOfStrength() << " damage.";
	std::cout << "  Its Health = " << monster.getCountOfHealth() << ".\n";
}

void Game::fightWithMonster() {
	char choice;
	bool hasMonster = true;

	while (hasMonster && !player.isDead()) {
		std::cout << "(R)un or (F)ight: ";
		std::cin >> choice;

		switch (choice) {
		case 'r':
			if (take_chance(50, 50)) {
				std::cout << "You successfully fled.\n";
				hasMonster = false;
				break;
			}
			else {
				monsterAttack();
				break;
			}
		case 'f':
			playerAttack();
			if (monster.isDead()) {
				std::cout << "You killed the " << monster.getName() << ".\n";
				hasMonster = false;

				player.addGold(monster.getCountOfGold());
				player.levelUp();
			}
			else {
				monsterAttack();
			}
			break;
		default: std::cout << "bip... wrong literal.\n";
		}
	}
}

void Game::play() {
	while (!player.isDead() && !player.hasWon()) {
		monster = Monster::getRandomMonster();
		std::cout << "\nYou have encountered a " << monster;
		std::cout << " Health = " << monster.getCountOfHealth() << ", Strenght = " << monster.getCountOfStrength();
		std::cout << "\t" << player.getName() << "( Health = " << player.getCountOfHealth() << ", Strenght = " << player.getCountOfStrength() << " )\n";

		fightWithMonster();
	}
}

void Game::printResult() {
	std::cout << "\n";
	if (player.isDead()) {
		std::cout << "You died.\n";
	}
	else {
		std::cout << "You win!\n";
	}
	std::cout << "( Level = " << player.getLevel() << ", gold = " << player.getCountOfGold() << " ).\n";
}