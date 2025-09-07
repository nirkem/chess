#include <iostream>
#include <vector>
#include <string>
#include "headers/Board.h"
#include "headers/Player.h"
#include <conio.h>

using namespace std;

int main() {
    
    cout << "Welcome to Nir's Chess game!" << endl << endl;
    cout << "In this game, we perform moves by specifying the origin square and the destination square." << endl;
    cout << "For example, to move Pawn d2 to square d4, you need to enter: d2d4 in the console." << endl << endl;
    cout << "In case of a pawn promotion, enter the move followed by the symbol of the new piece." << endl;
    cout << "For example, to move Pawn b7 to b8 and promote to queen, you need to enter: b7b8Q in the console" << endl << endl;
    cout << "On the board, white pieces are represented by capital letters and black by lowercase letters." << endl;
    cout << "Remember that white always starts the game." << endl << endl;

    cout << "Have Fun!" << endl;
    cout << "Press any key to start..." << endl;
    _getch();

    // initialize Players


    // display board
    Board* board = new Board();
    board->display_board();
    bool playing{true};
    bool move_succeeded;

    string move;
    int turn{0};

    while (playing) {
        cout << "Please enter a move: ";
        cin >> move;
        move_succeeded = board->move(move, turn);

        if (move_succeeded) {
            board->display_board();
            turn = (turn == 0) ? 1 : 0;

        } else {
            cout << "Illegal Move" << endl;
            continue;
        }
        
    }

    return 0;
}