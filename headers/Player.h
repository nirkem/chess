#pragma once
#include <string>
#include <vector>
#include "Piece.h"

class Player {
    private:
        std::vector<Piece*>* pieces;

    public:
        Player(bool is_white, bool is_winner);
};