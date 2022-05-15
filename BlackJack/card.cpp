#include "card.h"

std::ostream& operator<< (std::ostream& out, const Card& card) {
	out << card.getRank() << ' ' << card.getSuit();
	return out;
}
bool Card::operator==(const Card& other) {
	return ((this->rank == other.rank) && (this->suit == other.suit));
}

std::string Card::getRank() const {
	switch (rank) {
	case Rank::RANK_2:  return "Two";
	case Rank::RANK_3:  return "Three";
	case Rank::RANK_4:  return "Four";
	case Rank::RANK_5:  return "Five";
	case Rank::RANK_6:  return "Six";
	case Rank::RANK_7:  return "Seven";
	case Rank::RANK_8:  return "Eight";
	case Rank::RANK_9:  return "Nine";
	case Rank::RANK_10: return "Ten";
	case Rank::JACK:    return "Jack";
	case Rank::QUEEN:   return "Queen";
	case Rank::KING:    return "King";
	case Rank::ACE:     return "Ace";
	}

	return "error";
}

std::string Card::getSuit() const {
	switch (suit) {
	case Suit::CLUBS:    return "Clubs";
	case Suit::DIAMONDS: return "Diamonds";
	case Suit::SPADES:   return "Spades";
	case Suit::HEARTS:   return "Hearts";
	}

	return "error";
}

void Card::setRank(Rank rank) {
	this->rank = rank;
}

void Card::setSuit(Suit suit) {
	this->suit = suit;
}

int Card::getCardValue() {
	switch (rank) {
	case Rank::RANK_2: return 2;
	case Rank::RANK_3: return 3;
	case Rank::RANK_4: return 4;
	case Rank::RANK_5: return 5;
	case Rank::RANK_6: return 6;
	case Rank::RANK_7: return 7;
	case Rank::RANK_8: return 8;
	case Rank::RANK_9: return 9;
	case Rank::RANK_10: return 10;
	case Rank::JACK: return 10;
	case Rank::QUEEN: return 10;
	case Rank::KING: return 10;
	case Rank::ACE: return 11;
	}

	return 0;
}
