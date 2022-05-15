#pragma once

#include "deck.h"

class BlackJack {
private:

	class Member {
	private:
		Card* cards;
		size_t count_cards;
		size_t count_points;
		bool isBlackJack;

	public:
		Member() : cards(nullptr), count_cards(0), count_points(0), isBlackJack(false)
		{
		}
		Member(const Member& other);

		~Member();

		size_t getPoints();
		Card getLastCard();
		bool getIsBlackJack();

		void calculatePoints(Card& last_carde);
		void takeCard(Deck& deck);
	};

private:
	Deck deck;
	static size_t count_take_cards;

	Member dealer;
	Member player;

	int result;

public:
	BlackJack() : result(0)
	{
	}

	void startGame();
	void dealerTurn();
	void playerTurn();
	void resultGame();

	std::string getResultGame();
};
