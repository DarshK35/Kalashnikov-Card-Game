#pragma once
#include <stdlib.h>
#include <time.h>

enum suits { SPADE = 0, HEART, CLUB, DIAMOND };

struct card {
    int value, strength;
    int suit;

    void operator = (card& c) {
        value = c.value;
        strength = c.strength;
        suit = c.suit;
    }

    bool operator == (card& c) {
        int v = c.value;
        int st = c.strength;
        int su = c.suit;
        if(v == value && st == strength && su == suit) {
            return true;
        }
        else {
            return false;
        }
    }

    void get_strength();
    void disp();
};

void swap(card&, card&);

class card_deck {
    private:
        card cards[52], shelf[16], garbage[36];
        int shelf_cards, garbage_cards, position;

        void init_cards();
        void shuffle();

    public:
        card_deck();

        card pick_from_deck();
        card pick_from_shelf(int);
        void put_to_shelf(card);
        void put_to_garbage(card);

        void view_shelf();
        void view_garbage();
        void view_deck();
};

class player {
    private:
        card hand[4], picked;
        int score;

    public:
        player();

        void shuffle_hand();
        void pick_card();
        card discard_card(int);
        card put_card_shelf(int);
        int calc_damage(int);

        void start();

        void view_hand();
        void view_picked();
        void view_score();
};


void card_deck::init_cards() {
    for (int i = 0; i < 52; i++) {
        cards[i].value = (i % 13) + 1;
        cards[i].get_strength();
    }

    int suit = SPADE;
    for (int i = 1; i <= 52; i++) {
        cards[i - 1].suit = suit;
        switch (i) {
            case 13:
                suit = HEART;
                break;

            case 26:
                suit = CLUB;
                break;

            case 39:
                suit = DIAMOND;
                break;
        }
    }
}
void card_deck::shuffle() {
    srand(time(NULL));
    for (int i = 1; i < 52; i++)
        swap(cards[i], cards[rand() % i]);
}
card_deck::card_deck() {
    init_cards();
    shuffle();
    shelf_cards = 0;
    garbage_cards = 0;
    position = 0;
}

card card_deck::pick_from_deck() {
    position++;
    return cards[position - 1];
}
card card_deck::pick_from_shelf(int pos) {
    card temp = shelf[pos];
    for (int i = pos; i < shelf_cards - 1; i++)
        shelf[i] = shelf[i + 1];
    shelf_cards--;
    return temp;
}
void card_deck::put_to_garbage(card to_put) {
    garbage[garbage_cards] = to_put;
    garbage_cards++;
}
void card_deck::put_to_shelf(card to_put) {
    shelf[shelf_cards] = to_put;
    shelf_cards++;
}

player::player() {
    score = 0;
}
void player::shuffle_hand() {
    srand(time(NULL));
    for (int i = 1; i < 4; i++)
        swap(hand[i], hand[rand() % i]);
}
int player::calc_damage(int pos) {
    card to_calc = hand[pos];
    card *hand_copy = new card[4];

    //Creating sorted copy of the hand
    for(int i = 0; i < 4; i++) {
        hand_copy[i] = hand[i];
    }

    int highest_val, p = 0;
    for(int i = 0; i < 3; i++) {
        highest_val = hand_copy[i].strength;
        p = i;
        for(int j = i + 1; j < 4; j++) {
            if(highest_val < hand_copy[j].strength) {
                highest_val = hand_copy[j].strength;
                p = j;
            }
        }
        swap(hand_copy[i], hand_copy[p]);
    }

    //Calculating damage
    int damage = 5;
    for(int i = 0; i < 4; i++) {
        if(hand[i - 1].strength != hand[i].strength && i > 0) {
            damage--;
        }

        if(hand[i] == to_calc) {
            return damage;
        }
    }
}

void swap(card& a, card& b) {
    card tem;
    tem = a;
    a = b;
    b = tem;
}
void card::get_strength() {
    switch(value) {
        case 1:
            strength = 13;
            break;

        case 13:
            strength = 12;
            break;

        case 12:
            strength = 11;
            break;

        case 11:
            strength = 10;
            break;

        default:
            strength = value - 1;
    }
}
