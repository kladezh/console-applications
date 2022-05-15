#include "creature.h"

void Creature::reduceHealth(int count_hit) {
	assert(count_hit >= 0);
	health -= count_hit;
}

void Creature::addGold(int count_gold) {
	assert(count_gold >= 0);
	gold += count_gold;
}

std::string Creature::getName() {
	return name;
}

char Creature::getSymdol() {
	return symbol;
}

int Creature::getCountOfHealth() {
	return health;
}

int Creature::getCountOfStrength() {
	return strength;
}

int Creature::getCountOfGold() {
	return gold;
}

bool Creature::isDead() {
	return (health <= 0);
}
