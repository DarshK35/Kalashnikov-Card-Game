#include <iostream>
#include <fstream>
#include <conio.h>
#include "GameData.h"
using namespace std;

card_deck deck;
player p1, comp;

char menu();
void game();
void instructions();

void player_turn();
void comp_turn();

int main() {
    char e;
    do {
        e = menu();
    } while(e != 'e');
}

char menu() {
    system("cls");
    char ch, e;

    cout << "Kalashnikov - The Card Game";
    cout << "Main Menu";
    cout << "\nP -> Play Game";
    cout << "\nI -> Instructions";
    cout << "\nE -> Exit Game";

    ch = _getch();
    switch(ch){
        case 'p':
            game();
            break;

        case 'i':
            instructions();
            break;

        case 'e':
            cout << "\n\nAre you sure? (Y / N)";
            sure_exit:
            e = _getch();

            switch(e) {
                case 'y':
                    break;

                case 'n':
                    ch = e;
                    break;

                default:
                    goto sure_exit;
            }
    }
    return ch;
}
void game() {
    p1.start();
    comp.start();
    do {
        player_turn();
        comp_turn();
        break;
    } while(p1.ret_score() < 20 && comp.ret_score() < 20);

    system("cls");
    cout << "Game Over";

    if(p1.ret_score() > comp.ret_score()) {
        cout << "\n\nYou Win";
    }
    else {
        cout << "\n\nYou Lose";
    }

    cout << "\n\nPress any key to return to menu";
    _getch();
}
void instructions() {
    system("cls");
    fstream file;
    char ch;

    file.open("Instructions_screen.dat", ios::in);
    while(!file.eof()) {
        ch = file.get();
        cout << ch;
    }
    _getch();
}

void player_turn() {
    char ch;
    system("cls");
    cout << "\nYour hand:\n";
    p1.view_hand();

    cout << "\n" << 52 - deck.position << " cards in deck";

    cout << "\n\nYour choices:";
    if(p1.kalashnikov())
        cout << "\nK -> KALASHNIKOV CYKA!";
    if(52 - deck.position > 0)
        cout << "\nD -> Pick card from deck";
    //if(deck.shelf_cards)
}
void comp_turn() {

}

void card_deck::view_shelf() {

}
void card_deck::debug_view() {
    for(int i = 0; i < 52; i++) {
        cards[i].disp();
    }
}

void player::start() {
    for(int i = 0; i < 4; i++) {
        pick_card(-1);
        hand[i] = picked;
    }
}
void player::pick_card(int c) {
    if(c == -1)
        equate(deck.pick_from_deck());
    else
        equate(deck.pick_from_shelf(c));
}
void player::discard_card(int pos) {
    switch(pos) {
        case 4:
            deck.put_to_garbage(picked);
            break;
        default:
            deck.put_to_garbage(hand[pos]);
            hand[pos] = picked;
    }
}
void player::put_card_shelf(int pos) {
    switch(pos) {
        case 4:
            deck.put_to_shelf(picked);
            break;
        default:
            deck.put_to_shelf(hand[pos]);
            hand[pos] = picked;
    }
}
void player::view_hand() {
    for(int i = 0; i < 4; i++) {
        hand[i].disp();
    }
}
void player::view_picked() {
    picked.disp();
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
