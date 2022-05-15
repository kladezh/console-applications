#pragma once

#include <iostream>

class Card {
public:
	enum class Suit
	{
		HEARTS,
		DIAMONDS,
		CLUBS,
		SPADES,
		MAX_SUITS
	};

	enum class Rank
	{
		RANK_2,
		RANK_3,
		RANK_4,
		RANK_5,
		RANK_6,
		RANK_7,
		RANK_8,
		RANK_9,
		RANK_10,
		JACK,
		QUEEN,
		KING,
		ACE,
		MAX_RANKS
	};

private:
	Rank rank;
	Suit suit;

public:
	Card() : rank(Rank::MAX_RANKS), suit(Suit::MAX_SUITS)
	{
	}
	Card(Rank rank, Suit suit) : rank(rank), suit(suit)
	{
	}
	Card(const Card& other) : rank(other.rank), suit(other.suit)
	{
	}

	friend std::ostream& operator<< (std::ostream& out, const Card& card);
	bool operator== (const Card& other);

	std::string getRank() const;
	std::string getSuit() const;

	void setRank(Rank rank);
	void setSuit(Suit suit);

	int getCardValue();
};
