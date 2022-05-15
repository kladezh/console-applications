#include <iostream>
#include <cassert>

#define MAX_LEVEL 20

size_t range_rand(size_t left, size_t right) {
	return left + rand() % (right - left + 1);
}

bool take_chance(size_t bad, size_t good) {
	size_t* arr = new size_t[bad + good];
	for (size_t i = 0; i < bad + good; i++) {
		if (i < bad) {
			arr[i] = 0;
		}
		else {
			arr[i] = 1;
		}
	}

	bool chance = static_cast<bool>(arr[range_rand(0, static_cast<int>(bad + good))]);

	delete[] arr;
	return chance;
}

// CREATURE
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

// PLAYER
class Player : public Creature {
private:
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

// MONSTER
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
		: Creature(monsterData[static_cast<int>(type)].name,
			monsterData[static_cast<int>(type)].symbol,
			monsterData[static_cast<int>(type)].health,
			monsterData[static_cast<int>(type)].strength,
			monsterData[static_cast<int>(type)].gold)
	{
	}

	friend std::ostream& operator<< (std::ostream& out, const Monster& monster);

	static Monster getRandomMonster();
};

Monster::MonsterData Monster::monsterData[static_cast<int>(MonsterType::MAX_TYPES)]{
	{ "dragon", 'D', 20, 4, 100 },
	{ "orc", 'O', 4, 2, 25 },
	{ "slime",'S', 1, 1, 10 }
};

//DUNGEON
class Game {
private:
	Player player;
	Monster monster;

	void monsterAttack();
	void playerAttack();
	void fightWithMonster();

public:
	void setPlayerName();
	void play();
	void printResult();
};

// MAIN =====================================
int main() {
	srand(time(NULL));

	Game game;

	game.setPlayerName();
	game.play();
	game.printResult();

	return 0;
}
// ==========================================

// CREATURE
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

// PLAYER
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

// MONSTER
std::ostream& operator<<(std::ostream& out, const Monster& monster) {
	out << monster.name << " (" << monster.symbol << "):";

	return out;
}

Monster Monster::getRandomMonster() {
	size_t num = range_rand(0, static_cast<int>(MonsterType::MAX_TYPES) - 1);

	return Monster(static_cast<MonsterType>(num));
}

// GAME
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
