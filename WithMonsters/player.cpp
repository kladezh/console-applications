#include "player.h"

std::ostream& operator<< (std::ostream& out, const Player& player) {
	out << "You have " << player.health << " health and are carrying " << player.gold << " gold.";

	return out;
}

void Player::levelUp() {
	level++;
	strength++;
}

int Player::getLevel() {
	return level;
}

void Player::setName(std::string name) {
	this->name = name;
}

bool Player::hasWon() {
	return (level >= MAX_LEVEL);
}
