#include "../headers/Bishop.h"
#include <iostream>

Bishop::Bishop(int col, int row, bool is_white) : Piece(col, row, is_white) {
    if (is_white) this->symbol = 'B';
    else this->symbol = 'b';
}

bool Bishop::move(int new_col, int new_row, int player, Piece* const (&brd)[24][24]) {
    int col_abs_diff = std::abs(new_col - col);
    int row_abs_diff = std::abs(new_row - row);
    if (new_row == row ||
        new_col == col ||
        col_abs_diff != row_abs_diff) {
        std::cout << "Invalid move for white bishop." << std::endl;
        return false;
    }
    // handle WHITE
    if (is_white) {
        if (new_col > col && new_row > row) {
            for (int c = col + 3, r = row + 3; c < new_col && r < new_row; c += 3, r += 3) {
                if (brd[c][r] != nullptr) {
                    std::cout << "Path blocked for white bishop." << std::endl;
                    Piece* blocking_piece = brd[c][r];
                    std::cout << "Blocking piece symbol: " << (blocking_piece ? blocking_piece->get_symbol() : ' ') << std::endl;
                    return false;
                }
            }
        }
        else if (new_col > col && new_row < row) {
            for (int c = col + 3, r = row - 3; c < new_col && r > new_row; c += 3, r -= 3) {
                if (brd[c][r] != nullptr) {
                    std::cout << "Path blocked for white bishop." << std::endl;
                    Piece* blocking_piece = brd[c][r];
                    std::cout << "Blocking piece symbol: " << (blocking_piece ? blocking_piece->get_symbol() : ' ') << std::endl;
                    return false;
                }
            }
        }
        else if (new_col < col && new_row > row) {
            for (int c = col - 3, r = row + 3; c > new_col && r < new_row; c -= 3, r += 3) {
                if (brd[c][r] != nullptr) {
                    std::cout << "Path blocked for white bishop." << std::endl;
                    Piece* blocking_piece = brd[c][r];
                    std::cout << "Blocking piece symbol: " << (blocking_piece ? blocking_piece->get_symbol() : ' ') << std::endl;
                    return false;
                }
            }
        }
        else if (new_col < col&& new_row < row) {
            for (int c = col - 3, r = row - 3; c > new_col && r > new_row; c -= 3, r -= 3) {
                if (brd[c][r] != nullptr) {
                    std::cout << "Path blocked for white bishop." << std::endl;
                    Piece* blocking_piece = brd[c][r];
                    std::cout << "Blocking piece symbol: " << (blocking_piece ? blocking_piece->get_symbol() : ' ') << std::endl;
                    return false;
                }
            }
        }
        if (brd[new_col][new_row] != nullptr) {
            Piece* piece_to_kill = brd[new_col][new_row];
            if (piece_to_kill->isWhite()) {
                std::cout << "Invalid move for white bishop." << std::endl;
                std::cout << "Cannot capture own piece." << std::endl;
                return false;
            }
        }
        else {
            // regular move
            col = new_col;
            row = new_row;

            return true;
        }
    }
    // handle BLACK
    else {
        if (new_col > col && new_row > row) {
            for (int c = col + 3, r = row + 3; c < new_col && r < new_row; c += 3, r += 3) {
                if (brd[c][r] != nullptr) {
                    std::cout << "Path blocked for black bishop." << std::endl;
                    Piece* blocking_piece = brd[c][r];
                    std::cout << "Blocking piece symbol: " << (blocking_piece ? blocking_piece->get_symbol() : ' ') << std::endl;
                    return false;
                }
            }
        }
        else if (new_col > col && new_row < row) {
            for (int c = col + 3, r = row - 3; c < new_col && r > new_row; c += 3, r -= 3) {
                if (brd[c][r] != nullptr) {
                    std::cout << "Path blocked for black bishop." << std::endl;
                    Piece* blocking_piece = brd[c][r];
                    std::cout << "Blocking piece symbol: " << (blocking_piece ? blocking_piece->get_symbol() : ' ') << std::endl;
                    return false;
                }
            }
        }
        else if (new_col < col && new_row > row) {
            for (int c = col - 3, r = row + 3; c > new_col && r < new_row; c -= 3, r += 3) {
                if (brd[c][r] != nullptr) {
                    std::cout << "Path blocked for black bishop." << std::endl;
                    Piece* blocking_piece = brd[c][r];
                    std::cout << "Blocking piece symbol: " << (blocking_piece ? blocking_piece->get_symbol() : ' ') << std::endl;
                    return false;
                }
            }
        }
        else if (new_col < col&& new_row < row) {
            for (int c = col - 3, r = row - 3; c > new_col && r > new_row; c -= 3, r -= 3) {
                if (brd[c][r] != nullptr) {
                    std::cout << "Path blocked for black bishop." << std::endl;
                    Piece* blocking_piece = brd[c][r];
                    std::cout << "Blocking piece symbol: " << (blocking_piece ? blocking_piece->get_symbol() : ' ') << std::endl;
                    return false;
                }
            }
        }
        if (brd[new_col][new_row] != nullptr) {
            Piece* piece_to_kill = brd[new_col][new_row];
            if (!piece_to_kill->isWhite()) {
                std::cout << "Invalid move for black bishop." << std::endl;
                std::cout << "Cannot capture own piece." << std::endl;
                return false;
            }
        }
        else {
            // regular move
            col = new_col;
            row = new_row;
            return true;
        }
    }
    return true;
}

bool Bishop::getHasMoved() const {
    return has_moved;
}