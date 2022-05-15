#include <iostream>

#define DECK_COUNT 52
#define MAX_COUNT_CARDS_IN_BLACKJACK 7

size_t brand(size_t left, size_t right) {
	return left + rand() % (right - left + 1);
}

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
	int getCardValue();
	void setRank(Rank rank);
	void setSuit(Suit suit);
};

std::ostream& operator<< (std::ostream& out, const Card& card) {
	out << card.getRank() << ' ' << card.getSuit();
	return out;
}
bool Card::operator==(const Card& other) {
	return ((this->rank == other.rank) && (this->suit == other.suit));
}

std::string Card::getRank() const {
	switch (rank) {
	case Rank::RANK_2: return "Two";
	case Rank::RANK_3: return "Three";
	case Rank::RANK_4: return "Four";
	case Rank::RANK_5: return "Five";
	case Rank::RANK_6: return "Six";
	case Rank::RANK_7: return "Seven";
	case Rank::RANK_8: return "Eight";
	case Rank::RANK_9: return "Nine";
	case Rank::RANK_10: return "Ten";
	case Rank::JACK: return "Jack";
	case Rank::QUEEN: return "Queen";
	case Rank::KING: return "King";
	case Rank::ACE: return "Ace";
	}

	return "error";
}

std::string Card::getSuit() const {
	switch (suit) {
	case Suit::CLUBS: return "Clubs";
	case Suit::DIAMONDS: return "Diamonds";
	case Suit::SPADES: return "Spades";
	case Suit::HEARTS: return "Hearts";
	}

	return "error";
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

void Card::setRank(Rank rank) {
	this->rank = rank;
}

void Card::setSuit(Suit suit) {
	this->suit = suit;
}

class Deck {
private:
	Card deck[DECK_COUNT];

public:
	Deck();

	friend std::ostream& operator<< (std::ostream& out, const Deck& deck);
	Card& operator[] (size_t index);

	void swapCards(Card card_1, Card card_2);
	void shuffleDeck();
};

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
		num = brand(0, DECK_COUNT - 1);
		swapCards(deck[i], deck[num]);
	}
}


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
		~Member()
		{
			if (cards != nullptr) {
				delete[] cards;
				cards = nullptr;
			}
		}
		Member(const Member& other);

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

size_t BlackJack::count_take_cards = 0;

BlackJack::Member::Member(const Member& other)
{
	this->cards = new Card[other.count_cards];
	for (size_t i = 0; i < other.count_cards; i++) {
		this->cards[i] = other.cards[i];
	}
	this->count_cards = other.count_cards;
	this->count_points = other.count_points;
	this->isBlackJack = other.isBlackJack;
}

size_t BlackJack::Member::getPoints() {
	return count_points;
}

Card BlackJack::Member::getLastCard() {
	return cards[count_cards - 1];
}

bool BlackJack::Member::getIsBlackJack() {
	return isBlackJack;
}

void BlackJack::Member::calculatePoints(Card& last_carde) {
	if (last_carde.getCardValue() == 11 && count_points + 11 > 21) {
		count_points++;
	}
	else {
		count_points += last_carde.getCardValue();
	}

	if (count_points == 21) {
		isBlackJack = true;
	}
}

void BlackJack::Member::takeCard(Deck& deck) {
	Card* temp;

	if (count_cards == 0) {
		temp = new Card;
	}
	else {
		temp = new Card[count_cards + 1];
		for (size_t i = 0; i < count_cards; i++) {
			temp[i] = cards[i];
		}

		delete[] cards;
		cards = nullptr;
	}

	cards = temp;
	temp = nullptr;

	cards[count_cards] = deck[count_take_cards];
	calculatePoints(cards[count_cards]);

	count_cards++;
	count_take_cards++;
}

std::string BlackJack::getResultGame() {
	switch (result) {
	case 0: return "Draw";
	case -1: return "You lost";
	case 1: return "You win";
	}
}

void BlackJack::dealerTurn() {
	while (dealer.getPoints() < 17) {
		dealer.takeCard(deck);
		std::cout << "dealer taked " << dealer.getLastCard() << " and it\'s " << dealer.getPoints() << " POINTS\n\n";
	}
}

void BlackJack::playerTurn() {
	bool end_of_turn = false;
	int choice;

	while (!end_of_turn && !player.getIsBlackJack()) {

		std::cout << "1 - hit; 2 - stand;\n";
		std::cin >> choice;

		switch (choice) {
		case 1: // hit
			player.takeCard(deck);
			std::cout << "player taked " << player.getLastCard() << " and it\'s " << player.getPoints() << " POINTS\n\n";
			if (player.getPoints() > 21) {
				end_of_turn = true;
			}
			break;
		case 2: // stand
			end_of_turn = true;
			break;
		default:
			std::cout << "Wrong number... \n";
			break;
		}

	}
}

void BlackJack::resultGame() {
	size_t d_points = dealer.getPoints();
	size_t p_points = player.getPoints();

	if (d_points > 21 && p_points > 21) {
		result = 0;
	}
	else if (d_points > 21) {
		result = 1;
	}
	else if (p_points > 21) {
		result = -1;
	}
	else if (d_points == p_points) {
		result = 0;
	}
	else if (p_points > d_points) {
		result = 1;
	}
	else {
		result = -1;
	}
}

void BlackJack::startGame() {
	deck.shuffleDeck();

	dealer.takeCard(deck);
	std::cout << "dealer taked " << dealer.getLastCard() << " and it\'s " << dealer.getPoints() << " POINTS\n\n";

	player.takeCard(deck);
	std::cout << "player taked " << player.getLastCard() << " and it\'s " << player.getPoints() << " POINTS\n\n";
	player.takeCard(deck);
	std::cout << "player taked " << player.getLastCard() << " and it\'s " << player.getPoints() << " POINTS\n\n";

	playerTurn();

	dealerTurn();

	resultGame();
}

int main() {
	srand(time(NULL));

	BlackJack game;
	game.startGame();

	std::cout << "Result is: " << game.getResultGame() << std::endl;

	return 0;
}
