#include "../headers/King.h"
#include <iostream>

King::King(int col, int row, bool is_white) : Piece(col, row, is_white) {
    if (is_white) this->symbol = 'K';
    else this->symbol = 'k';
}

bool King::move(int new_col, int new_row, int player, Piece* const (&brd)[24][24]) {
    int col_abs_diff = std::abs(new_col - col);
    int row_abs_diff = std::abs(new_row - row);

    if (col_abs_diff <= 3 && row_abs_diff <= 3) {
        // Check for obstacles
        if (brd[new_col][new_row] != nullptr) {
            if (brd[new_col][new_row]->isWhite() == isWhite()) {
                std::cout << "Cannot capture own piece." << std::endl;
                return false;
            }
        }
        col = new_col;
        row = new_row;
        has_moved = true;
        return true;
    }
    return false;
}

bool King::getHasMoved() const {
    return has_moved;
}

bool King::isInCheck(Piece* const (&brd)[24][24]) {
    // Check if the king is in check by any opponent piece

    // check same row and col for Rook or Queen
    for (int i = 1; i < 24; i++) {
        if (brd[col][i] != nullptr) {
            if (brd[col][i]->isWhite() != isWhite()) {
                char symbol = brd[col][i]->get_symbol();
                if (symbol == 'r' || symbol == 'R' || symbol == 'q' || symbol == 'Q') {
                    return true;
                }
                else break; // blocked by other piece
            }
            else break; // blocked by own piece
        }
    }
    // check diagonals for Bishop or Queen or Pawn
    int directions[4][2] = { {1,1}, {1,-1}, {-1,1}, {-1,-1} };
    for (auto& dir : directions) {
        int n = 1;
        while (true) {
            int new_col = col + dir[0] * 3 * n;
            int new_row = row + dir[1] * 3 * n;
            if (new_col < 1 || new_col > 23 || new_row < 1 || new_row > 23) break; // out of bounds
            Piece* otherPiece = brd[new_col][new_row];
            if (otherPiece != nullptr) {
                if (otherPiece->isWhite() != isWhite()) {
                    char symbol = otherPiece->get_symbol();
                    if (symbol == 'b' || symbol == 'B' || symbol == 'q' || symbol == 'Q') {
                        return true;
                    }
                    // Check for pawn attack
                    if ((isWhite() && symbol == 'p' && dir[1] == -1) || (!isWhite() && symbol == 'P' && dir[1] == 1)) {
                        if (std::abs(dir[0]) == 1 && std::abs(dir[1]) == 1 && n == 1) {
                            return true;
                        }
                    }
                    break; // blocked by other piece
                }
                else break; // blocked by own piece
            }
            n++;
        }
    }
    // Check for Knight attacks
    int knight_moves[8][2] = { {6,3}, {6,-3}, {-6,3}, {-6,-3}, {3,6}, {3,-6}, {-3,6}, {-3,-6} };
    for (auto& move : knight_moves) {
        int new_col = col + move[0];
        int new_row = row + move[1];
        if (new_col >= 1 && new_col <= 23 && new_row >= 1 && new_row <= 23) {
            if (brd[new_col][new_row] != nullptr && brd[new_col][new_row]->isWhite() != isWhite()) {
                char symbol = brd[new_col][new_row]->get_symbol();
                if (symbol == 'n' || symbol == 'N') {
                    return true;
                }
            }
        }
    }
    return false;
}