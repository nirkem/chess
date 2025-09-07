#pragma once
#include "Piece.h"

class Queen : public Piece {
private:
    bool has_moved = false; // Track if pawn has moved (for double-step, en passant)

public:
    Queen(int col, int row, bool is_white);
    bool move(int new_col, int new_row, int player, Piece* const (&brd)[24][24]) override;
    bool getHasMoved() const;
};