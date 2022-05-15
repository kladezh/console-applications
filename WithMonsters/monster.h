#pragma once

#include "creature.h"
#include "functions.h"

class Monster : public Creature {
private:
	enum class MonsterType {
		DRAGON,
		ORC,
		SLIME,
		MAX_TYPES
	};

	struct MonsterData {
		std::string name;
		char symbol;
		int health;
		int strength;
		int gold;
	};

	static MonsterData monsterData[static_cast<int>(MonsterType::MAX_TYPES)];

public:
	Monster() : Creature()
	{
	}
	Monster(MonsterType type)
		: Creature(
			monsterData[static_cast<int>(type)].name,
			monsterData[static_cast<int>(type)].symbol,
			monsterData[static_cast<int>(type)].health,
			monsterData[static_cast<int>(type)].strength,
			monsterData[static_cast<int>(type)].gold)
	{
	}

	friend std::ostream& operator<< (std::ostream& out, const Monster& monster);

	static Monster getRandomMonster();
};