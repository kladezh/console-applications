#pragma once

#include "player.h"
#include "monster.h"

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

