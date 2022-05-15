#include "blackjack.h"

size_t BlackJack::count_take_cards = 0;

BlackJack::Member::Member(const Member& other) {
	this->cards = new Card[other.count_cards];
	for (size_t i = 0; i < other.count_cards; i++) {
		this->cards[i] = other.cards[i];
	}
	this->count_cards = other.count_cards;
	this->count_points = other.count_points;
	this->isBlackJack = other.isBlackJack;
}

BlackJack::Member::~Member() {
	if (cards != nullptr) {
		delete[] cards;
		cards = nullptr;
	}
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
