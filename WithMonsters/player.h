#pragma once

#include "creature.h"

class Player : public Creature {
private:
	static const int MAX_LEVEL = 20;

	int level;

public:
	Player() : Creature(), level(1)
	{
	}
	Player(std::string name) : Creature(name), level(1)
	{
	}
	Player(std::string name, char symbol, int health, int strength, int gold)
		: Creature(name, symbol, health, strength, gold), level(1)
	{
	}

	friend std::ostream& operator<< (std::ostream& out, const Player& player);

	int getLevel();
	void setName(std::string name);

	void levelUp();
	bool hasWon();
};

