#include <iostream>
#include <fstream>
#include <conio.h>
#include "GameDataTemp.h"
using namespace std;

cardDeck deck;
player p1, cpu;
availableActivities perms;

char menu();
void game();
void instructions();

int main() {
    char ex;
    do {
        ex = menu();
    } while(ex != 'e');
    return 0;
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
			exitMainMenu:
			e = _getch();

			switch(e) {
				case 'y':
					break;

				case 'n':
					ch = e;
					break;

				default:
					goto exitMainMenu;
			}
	}
	return ch;
}
//Still to be defined and implemented
void game() {
    deck.newGame();
    p1.start();
    cpu.start();

    int p1Score, cpuScore;
    bool gameOver = false;

    while(!gameOver) {
        char playerChoice;
        p1Score = p1.retScore();
        cpuScore = cpu.retScore();

        system("cls");
        //Display score, player hand and other info
        cout << "Your score: " << p1Score;
        cout << "\nCPU score" << cpuScore;
        cout << "\n\nYour hand:\n";
        p1.viewHand();

        cout << "Remaining Deck Cards: " << 53 - deck.deckCards;
        cout << "Remaining Shelf Cards: " << deck.shelfCards;

        perms.checkPreChoice(deck, p1);
        cout << "Available options:\n";
        if(perms.pickFromDeck) {
            cout << "D -> Pick from Deck";
        }
        if(perms.pickFromShelf) {
            cout << "S -> Pick from Shelf";
        }
        if(perms.kalashnikov) {
            cout << "K -> Kalashnikov cyka!";
        }
        playerFirstChoice:
        playerChoice = _getch();

        switch(playerChoice) {
            case 'd':
                if(perms.pickFromDeck) {
                    player.pickCard(0);
                    cout << "Card Picked from Deck";
                    break;
                } else {
                    goto playerFirstChoice;
                }

            case 's':
                if(perms.pickFromShelf) {
                    int pos;
                    cout << "\n\nShelf:\t" << deck.shelfCards << " cards\n";

                    shelfCardPosTell:
                    cout << "\nSpecify position to take card from: ";
                    cin >> pos;
                    if(pos < deck.shelfCards) {
                        player.pickCard(1, pos);
                        cout << "Card Picked from Shelf";
                    } else {
                        cout << "Invalid value, try again";
                        goto shelfCardsPosTell;
                    }
                } else {
                    goto playerFirstChoice;
                }

            case 'k':
                if(perms.kalashnikov) {
                    //Still have to add this gameplay scene

                    deck.newGame();
                    p1.afterKalashnikovStart();
                    cpu.afterKalashnikovStart();
                    if(p1Score >= 20) {
                        gameOver = true;
                    }
                    continue;
                } else {
                    goto playerFirstChoice;
                }

            default:
                goto playerFirstChoice;
        }

        cout << "\nPicked Card:\n";
        p1.viewSelected();

        perms.checkpostChoice(deck, p1);
        cout << "Available Options:\n";
        
    }
}
void instructions() {
    system("cls");
    fstream file;
    file.open("Instructions_screen.dat", ios::in);
    while(!file.eof()) {
        cout << file.get();
    }
    _getch();
}

//Leftover player functions that require player-deck interaction
void player::pickCard(int source, int pos = 0) {
    if(source == 0) {
        selected = deck.pickCard(source, pos);
    } else {
        selected = deck.pickCard(source, pos);
    }
}
void player::putCard(int dest, int handPos) {
    if(handPos == 4) {
        deck.putCard(dest, selected);
    } else {
        deck.putCard(dest, hand[handPos]);
    }
}