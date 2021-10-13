#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

enum suits {SPADE = 0, HEART, CLUB, DIAMOND};
const int kalashnikovHand[] = {13, 7, 4, 1};

struct card {
	int value, strength;
	int suit;

	void operator = (card& c);
	bool operator == (card& c);

	void getStrength();
	void disp(bool);
};

class cardDeck {
	private:
		card cards[52], shelf[16], garbage[36];

		void initCards();
		void shuffleDeck();

	public:
		int shelfCards, garbageCards, deckCards;

		cardDeck();
		void newGame();

		card pickCard(int, int);
		void putCard(int, card);

		void viewShelf();
		void viewDeck();
		void debugView();
};

class player {
	private:
		card hand[4], selected;
		int score;

	public:
		player();
		void start();
		void afterKalashnikovStart();

		void shuffleHand();
		int calcDamage(int);
		void addScore(int);
		int retScore();
		bool kalashnikov();

		void pickCard(int, int);
		void putCard(int, int);
		void swapWithHand(int);

		void viewHand();
		void viewSelected();
};

struct availableActivities {
	//First menu perms
	bool pickFromDeck, pickFromShelf, kalashnikov;
	//Picked card perms
	bool putToShelf, putToGarbage;

	void checkPreChoice(cardDeck, player);
	void checkPostChoice(cardDeck, player);
};

void cardSwap(card &a, card &b);


//Card Functions
void card::operator = (card& c) {
	value = c.value;
	strength = c.strength;
	suit = c.suit;
}
bool card::operator == (card& c) {
	if(c.value == value && c.strength == strength && c.suit == suit) {
		return true;
	} else {
		return false;
	}
}

void card::getStrength() {
	if(value == 1) {
		strength = 13;
	} else {
		strength = value - 1;
	}
}
void card::disp(bool mystery) {
	if(mystery) {
		cout << "??\t??\n";
		return;
	}
	switch(value) {
		case 1:
			cout << "A" << '\t';
			break;

		case 13:
			cout << "K" << '\t';
			break;

		case 12:
			cout << "Q" << '\t';
			break;

		case 11:
			cout << "J" << '\t';
			break;

		default:
			cout << value << '\t';
	}

	switch(suit) {
		case SPADE:
			cout << "Spade" << "\n";
			break;

		case HEART:
			cout << "Heart" << "\n";
			break;

		case CLUB:
			cout << "Club" << "\n";
			break;

		case DIAMOND:
			cout << "Diamond" << "\n";
	}
}


//Card Deck Functions
void cardDeck::initCards() {
	for(int i = 0; i < 52; i++) {
		cards[i].value = (i % 13) + 1;
		cards[i].getStrength();
	}

	int suit = SPADE;
	for(int i = 1; i <= 52; i++) {
		cards[i - 1].suit = suit;
		switch(i) {
			case 13:
				suit = HEART;
				break;

			case 26:
				suit = CLUB;
				break;

			case 39:
				suit = DIAMOND;
		}
	}
}
void cardDeck::shuffleDeck() {
	srand(time(NULL));
	for(int i = 1; i < 52; i++) {
		cardSwap(cards[i], cards[rand() % i]);
	}
}

cardDeck::cardDeck() {
	initCards();
	newGame();
}
void cardDeck::newGame() {
	shuffleDeck();
	shelfCards = garbageCards = deckCards = 0;
}

card cardDeck::pickCard(int source, int pos = 0) {
	/*
		Source value key:
		0: Deck
		1: Shelf
	*/
	if(source == 0) {
		deckCards++;
		return cards[deckCards - 1];
	} else {
		card ret = shelf[pos];
		for(int i = 0; i < shelfCards - 1; i++) {
			shelf[i] = shelf[i + 1];
		}
		return ret;
	}
}
void cardDeck::putCard(int dest, card toPut) {
	/*
		Dest key:
		0: Garbage
		1: Shelf
	*/
	srand(time(NULL));
	if(dest == 0) {
		garbage[garbageCards] = toPut;
		garbageCards++;
	} else {
		shelf[shelfCards] = toPut;
		shelfCards++;

		for(int i = 1; i < shelfCards; i++) {
			cardSwap(shelf[i], shelf[rand() % i]);
		}
	}
}

void cardDeck::viwShelf() {
	for(int i = 0; i < shelfCards; i++) {
		shelf[i].disp(true);
	}
}
void cardDeck::viewDeck() {
	for(int i = deckCards; i < 52; i++) {
		cards[i].disp(true);
	}
}
void cardDeck::debugView() {
	for(int i = 0; i < 52; i++) {
		cards[i].disp(false);
	}
}


//Player Functions
player::player() {
	score = 0;
}
void player::start() {
	for(int i = 0; i < 4; i++) {
		pickCard(0);
		hand[i] = selected;
	}
	selected = new card;
}

void player::shuffleHand() {
	srand(time(NULL));
	for(int i = 1; i < 4; i++) {
		cardSwap(hand[i], hand[rand() % i]);
	}
}
int player::calcDamage(int pos) {
	card toCalc = hand[pos];

	//Creating separate copy of hand
	card *handCopy = new card[4];
	for(int i = 0; i < 4; i++) {
		handCopy[i] = hand[i];
	}

	//Sorting the hand copy according to card Strength
	int max, p;
	for(int i = 0; i < 3; i++) {
		max = handCopy[i].strength;
		p = i;
		for(int j = i + 1; j < 4; j++) {
			if(max < handCopy[j].strength) {
				max = handCopy[j].strength;
				p = j;
			}
			swap(handCopy[i], handCopy[p]);
		}
	}

	//Calculating damage
	int damage = 5;
	for(int i = 0; i < 4; i++) {
		if(handCopy[i - 1].strength != handCopy[i].strength && i > 0) {
			damage--;
		}
		if(hand[i] == toCalc) {
			return damage;
		}
	}
}
void player::addScore(int increment) {
	score += increment;
}
int player::retScore() {
	return score;
}
bool player::kalashnikov() {
	//Creating separate copy of hand
	card *handCopy = new card[4];
	for(int i = 0; i < 4; i++) {
		handCopy[i] = hand[i];
	}

	//Sorting the hand copy according to card Strength
	int max, p;
	for(int i = 0; i < 3; i++) {
		max = handCopy[i].strength;
		p = i;
		for(int j = i + 1; j < 4; j++) {
			if(max < handCopy[j].strength) {
				max = handCopy[j].strength;
				p = j;
			}
			swap(handCopy[i], handCopy[p]);
		}
	}

	//Checking Kalashnikov condition
	for(int i = 0; i < 4; i++) {
		if(copy[i].value != kalashnikovHand[i]) {
			return false;
		}
	}
	return true;
}

void player::swapWithHand(int pos) {
	cardSwap(selected, hand[pos - 1]);
}

void player::viewHand() {
	for(int i = 0; i < 4; i++) {
		hand[i].disp(false);
	}
}
void player::viewSelected() {
	selected.disp(false);
}

//Other Functions
void cardSwap(card &a, card &b) {
	card temp = a;
	a = b;
	b = temp;
}
