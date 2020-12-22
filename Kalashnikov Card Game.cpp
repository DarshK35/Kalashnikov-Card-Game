#include <iostream>
#include <fstream>
#include <conio.h>
#include "GameData.h"
using namespace std;

card_deck deck;
player p1;

char menu();
void game();
void instructions();

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

void player::start() {
    for(int i = 0; i < 4; i++) {
        pick_card();
        hand[i] = picked;
    }
}
void player::pick_card() {
    card temp = deck.pick_from_deck();
    picked = temp;
}
void player::view_hand() {
    for(int i = 0; i < 4; i++) {
        hand[i].disp();
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
