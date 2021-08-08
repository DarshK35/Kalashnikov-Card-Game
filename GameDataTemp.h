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
	void disp();
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
		
		card pickCard(int);
		void putCard(int, card);
		
		void viewShelf();
		void viewGarbage();
		void debugView();
};

class player {
	private:
		card hand[4], selected;
		int score;
		
	public:
		player();
		void start();
		
		void shuffleHand();
		int calcDamage(int);
		void addScore(int);
		int retScore();
		bool kalashnikov();
		
		void pickCard(int);
		card putCard(int);
		
		void viewHand();
		void viewSelected();
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
void card::disp() {
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
			cout << "Spade" << "\t\n";
			break;

		case HEART:
			cout << "Heart" << "\t\n";
			break;

		case CLUB:
			cout << "Club" << "\t\n";
			break;

		case DIAMOND:
			cout << "Diamond" << "\t\n";
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
	
}
