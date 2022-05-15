#pragma once

#include "card.h"
#include "functions.h"

class Deck {
private:
	static const size_t DECK_COUNT = 52;

	Card deck[DECK_COUNT];

public:
	Deck();

	friend std::ostream& operator<< (std::ostream& out, const Deck& deck);
	Card& operator[] (size_t index);

	void swapCards(Card card_1, Card card_2);
	void shuffleDeck();
};
