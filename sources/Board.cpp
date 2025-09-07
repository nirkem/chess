#include "../headers/Board.h"
#include "../headers/Pawn.h"
#include "../headers/Rook.h"
#include "../headers/Knight.h"
#include "../headers/Queen.h"
#include "../headers/Bishop.h"
#include "../headers/King.h"
#include <iostream>

using namespace std;

void Board::delete_piece(Piece& piece) {
    // Get pointer to the object
    Piece* ptr = &piece;

    // Delete the object
    delete ptr;

    // Remove all pointers to this object from all vectors
    auto remove_ptr = [ptr](std::vector<Piece*>& vec) {
        vec.erase(std::remove(vec.begin(), vec.end(), ptr), vec.end());
        };

    remove_ptr(pieces);
    remove_ptr(white_pieces);
    remove_ptr(white_Pawns);
    remove_ptr(black_pieces);
    remove_ptr(black_Pawns);
}

char convert_to_char(int num) {
    num--;
    num += 'a';
    return char(num);
}

int convert_to_int(char c) {
    int num = int(c) - 96;
    return num;
}

bool is_legit_string(string s) {

    if (s[1] > '8' || s[1] < '1' || s[3] > '8' || s[3] < '1') return false;

    int first_char = int(s[0]);
    int second_char = int(s[2]);

    if (first_char < 97 || first_char > 104 || second_char < 97 || second_char > 104) return false;

    return true;
}

int* convert_string_to_col_row(string move) {
    int origin_col = convert_to_int(move[0]);
    int origin_row = move[1] - '0';
    int dest_col = convert_to_int(move[2]);
    int dest_row = move[3] - '0';

    int* ans = new int[5]();

    ans[0] = origin_col;
    ans[1] = origin_row;
    ans[2] = dest_col;
    ans[3] = dest_row;
    if (move.size() > 4) ans[4] = int(move[4]);

    return ans;
}

Board::Board() {
    legal_col_row = { 1, 4, 7, 10, 13, 16, 19, 22 };
    place_pieces();
}

void Board::display_board() {
    std::cout << std::endl << std::endl;
    const char white_square = ' ';      // white block
    const char black_square = char(219); // black block

    bool white = true;
    int col_counter = 0;
    int row_counter = 0;

    for (int row = 0; row < 24; row++) {
        for (int col = 0; col < 24; col++) {


            if (col_counter == 3) {
                white = !white;
                col_counter = 0;
            }
            if (brd[col][row] != nullptr) {
                // Print the piece
                cout << (brd[col][row])->get_symbol() << " ";
                col_counter++;
            }
            else {
                if (white) {
                    cout << white_square << white_square; // white square
                    col_counter++;
                }
                else {
                    cout << black_square << black_square; // black square
                    col_counter++;
                }
            }

        }

        if (std::find(legal_col_row.begin(), legal_col_row.end(), row) != legal_col_row.end()) cout << " | " << (row - 1) / 3 + 1;
        // else cout << " |   ";
        cout << endl;
        row_counter++;
        if (row_counter == 3) {
            white = !white;
            row_counter = 0;
        }
    }

    cout << "  ";
    for (int i = 1; i < 24; i++) {
        if (std::find(legal_col_row.begin(), legal_col_row.end(), i) != legal_col_row.end()) cout << "_" << " ";
        else cout << "  ";
    }

    cout << endl;
    cout << "  ";
    for (int i = 1; i < 24; i++) {
        char c = convert_to_char((i - 1) / 3 + 1);
        if (std::find(legal_col_row.begin(), legal_col_row.end(), i) != legal_col_row.end()) cout << c << " ";
        else cout << "  ";
    }
    cout << endl;
}

bool Board::move(string move, int turn) {

    if (!is_legit_string(move)) return false;

    bool wasInCheck = in_check;

    int* ans = convert_string_to_col_row(move);

    int origin_col = ans[0];
    int origin_row = ans[1];
    int dst_col = ans[2];
    int dst_row = ans[3];
    int new_piece = ans[4];

    Piece* piece = brd[3 * (origin_col - 1) + 1][3 * (origin_row - 1) + 1];
    if (piece == nullptr) {
        cout << "No piece at origin." << endl;
        return false;
    } 
    if (piece->isWhite() && turn == 1) {
        cout << "Black trying to move white piece" << endl;
        return false;
    }
    if (!piece->isWhite() && turn == 0) {
        cout << "White trying to move black piece" << endl;
        return false;
    }

    if (new_piece != 0) {
        // handle new piece move
    }
    else {
        // handle regular move
        Piece* dst = brd[3 * (dst_col - 1) + 1][3 * (dst_row - 1) + 1];
        if (dst == nullptr) {
            // perform regular move
            bool succeeded = piece->move(3 * (dst_col - 1) + 1, 3 * (dst_row - 1) + 1, turn, brd);
            if (succeeded) {
                brd[3 * (origin_col - 1) + 1][3 * (origin_row - 1) + 1] = nullptr;
                brd[3 * (dst_col - 1) + 1][3 * (dst_row - 1) + 1] = piece;

                if (wasInCheck) {
                    in_check = false;
                    if (turn == 0) {
                        if (white_king->isInCheck(brd)) {
                            in_check = true;
                            cout << "White king is still in check!" << endl;
                            // revert move
                            brd[3 * (origin_col - 1) + 1][3 * (origin_row - 1) + 1] = piece;
                            brd[3 * (dst_col - 1) + 1][3 * (dst_row - 1) + 1] = nullptr;
                            return false;
                        }
                    }
                    else {
                        if (black_king->isInCheck(brd)) {
                            in_check = true;
                            cout << "Black king is still in check!" << endl;
                            // revert move
                            brd[3 * (origin_col - 1) + 1][3 * (origin_row - 1) + 1] = piece;
                            brd[3 * (dst_col - 1) + 1][3 * (dst_row - 1) + 1] = nullptr;
                            return false;
                        }
                    }
                }
                checkForCheck(turn);
                return true;
            }
            else return false;
        }
        else {
            // handle kill_move
            bool succeeded = piece->move(3 * (dst_col - 1) + 1, 3 * (dst_row - 1) + 1, turn, brd);
            if (succeeded) {
                
                brd[3 * (origin_col - 1) + 1][3 * (origin_row - 1) + 1] = nullptr;
                brd[3 * (dst_col - 1) + 1][3 * (dst_row - 1) + 1] = piece;

                if (wasInCheck) {
                    in_check = false;
                    if (turn == 0) {
                        if (white_king->isInCheck(brd)) {
                            in_check = true;
                            cout << "White king is still in check!" << endl;
                            // revert move
                            brd[3 * (origin_col - 1) + 1][3 * (origin_row - 1) + 1] = piece;
                            brd[3 * (dst_col - 1) + 1][3 * (dst_row - 1) + 1] = dst;
                            pieces.push_back(dst);
                            if (dst->isWhite()) {
                                white_pieces.push_back(dst);
                                if (dst->get_symbol() == 'P')
                                    white_Pawns.push_back(dst);
                            }
                            else {
                                black_pieces.push_back(dst);
                                if (dst->get_symbol() == 'p')
                                    black_Pawns.push_back(dst);
                            }
                            return false;
                        }
                    }
                    else {
                        if (black_king->isInCheck(brd)) {
                            in_check = true;
                            cout << "Black king is still in check!" << endl;
                            // revert move
                            brd[3 * (origin_col - 1) + 1][3 * (origin_row - 1) + 1] = piece;
                            brd[3 * (dst_col - 1) + 1][3 * (dst_row - 1) + 1] = dst;
                            pieces.push_back(dst);
                            if (dst->isWhite()) {
                                white_pieces.push_back(dst);
                                if (dst->get_symbol() == 'P')
                                    white_Pawns.push_back(dst);
                            }
                            else {
                                black_pieces.push_back(dst);
                                if (dst->get_symbol() == 'p')
                                    black_Pawns.push_back(dst);
                            }
                            return false;
                        }
                    }
                }
                
                delete_piece(*dst);
                checkForCheck(turn);
                return true;
            } else return false;
        }
        checkForCheck(turn);
        return true;
    }
    return true;
}

void Board::place_pieces() {
    // Create black Pawns
    for (int col = 0; col < 8; col++) {
        brd[3 * col + 1][4] = new Pawn(3 * col + 1, 4, false);
        pieces.push_back(brd[(3 * col) + 1][4]);
    }

    // Create white Pawns
    for (int col = 0; col < 8; col++) {
        brd[3 * col + 1][19] = new Pawn(3 * col + 1, 19, true);
        pieces.push_back(brd[3 * col + 1][19]);
    }

    // Create Rook 
    brd[1][1] = new Rook(1, 1, false);
    brd[22][1] = new Rook(22, 1, false);
    brd[1][22] = new Rook(1, 22, true);
    brd[22][22] = new Rook(22, 22, true);
    pieces.push_back(brd[1][1]);
    pieces.push_back(brd[1][22]);
    pieces.push_back(brd[22][1]);
    pieces.push_back(brd[22][22]);

    // Create Knight
    brd[4][1] = new Knight(4, 1, false); brd[19][1] = new Knight(19, 1, false);
    brd[4][22] = new Knight(4, 22, true); brd[19][22] = new Knight(19, 22, true);
    pieces.push_back(brd[4][1]);
    pieces.push_back(brd[19][1]);
    pieces.push_back(brd[4][22]);
    pieces.push_back(brd[19][22]);

    // Create Bishop
    brd[7][1] = new Bishop(7, 1, false); brd[16][1] = new Bishop(16, 1, false);
    brd[7][22] = new Bishop(7, 22, true); brd[16][22] = new Bishop(16, 22, true);
    pieces.push_back(brd[7][1]);
    pieces.push_back(brd[16][1]);
    pieces.push_back(brd[7][22]);
    pieces.push_back(brd[16][22]);

    // Create Queen
    brd[13][1] = new Queen(13, 1, false);
    brd[13][22] = new Queen(13, 22, true);
    pieces.push_back(brd[13][1]);
    pieces.push_back(brd[13][22]);

    // Create King
    white_king = new King(10, 22, true);
    black_king = new King(10, 1, false);
    brd[10][1] = black_king;
    brd[10][22] = white_king;

    pieces.push_back(black_king);
    pieces.push_back(white_king);

    for (const auto& piece : pieces) {
        if (piece->isWhite()) {
            white_pieces.push_back(piece);
            if (piece->get_symbol() == 'P')
                white_Pawns.push_back(piece);
        }
        else {
            black_pieces.push_back(piece);
            if (piece->get_symbol() == 'p')
                black_Pawns.push_back(piece);
        }
    }
}

void Board::checkForCheck(int turn) {
    if (turn == 0) {
        in_check = black_king->isInCheck(brd);
        if (in_check) {
            cout << "Black king is in check!" << endl;
        }
    } 
    else {
        in_check = white_king->isInCheck(brd);
        if (in_check) {
            cout << "White king is in check!" << endl;
        }
    }
}