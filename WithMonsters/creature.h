#pragma once

#include <iostream>
#include <cassert>

class Creature {
private:

protected:
	std::string name;
	char symbol;
	int health;
	int strength;
	int gold;

public:
	Creature() : name(""), symbol('@'), health(10), strength(1), gold(0)
	{
	}
	Creature(std::string name) : name(name), symbol('@'), health(10), strength(1), gold(0)
	{
	}
	Creature(std::string name, char symbol, int health, int strength, int gold)
		: name(name), symbol(symbol), health(health), strength(strength), gold(gold)
	{
	}

	std::string getName();
	char getSymdol();
	int getCountOfHealth();
	int getCountOfStrength();
	int getCountOfGold();

	void reduceHealth(int count_hit);
	void addGold(int count_gold);
	bool isDead();
};
