#pragma once
#include <string>

class Piece {
protected:
    char symbol;
    int row, col;
    bool is_white;

public:
    Piece(int col, int row, bool is_white) : col(col), row(row), is_white(is_white) {}
    virtual bool move(int new_col, int new_row, int player, Piece* const (&brd)[24][24]) = 0;
    virtual ~Piece() = default;
    char get_symbol() const { return symbol; }
    int get_row() const { return row; }
    int get_col() const { return col; }
    void set_row(int row) { this->row = row; }
    void set_col(int col) { this->col = col; }
    bool isWhite() { return is_white; }
};