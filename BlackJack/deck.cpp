#include "deck.h"

Deck::Deck() {
	size_t i = 0;
	for (size_t suit = 0; suit < static_cast<size_t>(Card::Suit::MAX_SUITS); suit++) {
		for (size_t rank = 0; rank < static_cast<size_t>(Card::Rank::MAX_RANKS); rank++) {
			deck[i].setSuit(static_cast<Card::Suit>(suit));
			deck[i].setRank(static_cast<Card::Rank>(rank));
			i++;
		}
	}
}

std::ostream& operator<< (std::ostream& out, const Deck& deck) {
	for (const Card& card : deck.deck) {
		out << card << "\n";
	}

	return out;
}
Card& Deck::operator[] (size_t index) {
	return deck[index];
}

void Deck::swapCards(Card card_1, Card card_2) {
	int ind_1 = -1, ind_2 = -1;
	for (int i = 0; i < DECK_COUNT; i++) {
		if (deck[i] == card_1) {
			ind_1 = i;
			if (ind_2 != -1) {
				break;
			}
		}
		else if (deck[i] == card_2) {
			ind_2 = i;
			if (ind_1 != -1) {
				break;
			}
		}
	}

	if (ind_1 != -1 && ind_2 != -1) {
		Card temp = deck[ind_1];
		deck[ind_1] = deck[ind_2];
		deck[ind_2] = temp;
	}
}

void Deck::shuffleDeck() {
	size_t num;
	for (size_t i = 0; i < DECK_COUNT; i++) {
		num = range_rand(0, DECK_COUNT - 1);
		swapCards(deck[i], deck[num]);
	}
}