#include <iostream>
#include <fstream>
#include <conio.h>
using namespace std;

cardDeck deck;
player p1, cpu;

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
//Still to be defined and implemented
void game() {

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
