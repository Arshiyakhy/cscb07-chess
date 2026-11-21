#ifndef BOARD_H
#define BOARD_H
#include <array>
#include <memory>
#include "piece.h"
#include "position.h"

class Board {
private:
    std::array<std::array<char, 8>, 8> grid;
public:
    Board(){
        grid = {{
            {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}, // Rank 8 (Black)
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'}, // Rank 7
            {'.', '.', '.', '.', '.', '.', '.', '.'}, // Rank 6
            {'.', '.', '.', '.', '.', '.', '.', '.'}, // Rank 5
            {'.', '.', '.', '.', '.', '.', '.', '.'}, // Rank 4
            {'.', '.', '.', '.', '.', '.', '.', '.'}, // Rank 3
            {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'}, // Rank 2
            {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}  // Rank 1 (White)
        }};
    }
};

#endif 