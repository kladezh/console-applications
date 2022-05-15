#include "monster.h"

Monster::MonsterData Monster::monsterData[static_cast<int>(MonsterType::MAX_TYPES)]{
	{ "dragon", 'D', 20, 4, 100 },
	{ "orc", 'O', 4, 2, 25 },
	{ "slime",'S', 1, 1, 10 }
};

std::ostream& operator<<(std::ostream& out, const Monster& monster) {
	out << monster.name << " (" << monster.symbol << "):";

	return out;
}

Monster Monster::getRandomMonster() {
	size_t num = range_rand(0, static_cast<int>(MonsterType::MAX_TYPES) - 1);

	return Monster(static_cast<MonsterType>(num));
}
