#pragma once
#include <stdlib.h>
#include <time.h>

enum suits {SPADE = 0, HEART, CLUB, DIAMOND};

struct card
{
    int value, use;
    int suit;

    void operator = (card &c)
    {
        value = c.value;
        use = c.use;
        suit = c.suit;
    }
};

class card_deck
{
private:
    card cards[52], shelf[16], garbage[36];
    int shelf_cards, position;

    void init_cards();
    void shuffle();

public:
    card_deck();

    card pick_from_deck();
    card pick_from_shelf(int);
    void put_to_shelf(card);
    void put_to_garbage(card);
};

class player
{
private:
    card hard[4], picked;
    int score;

public:
    player();

    void shuffle_hand();
    void pick_card();
    card discard_card(int);
    card put_card_shelf(int);
    int calc_damage(int);
};
