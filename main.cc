#include <iostream>
#include "board.h"
#include "level1.h"

int main()
{
    Board b;
    b.setupStart();
    Level1 white, black;
    Colour turn = Colour::WHITE;

    for (int ply = 0; ply < 300; ++ply)
    { // stop after 300 moves max
        if (b.isCheckmate(turn))
        {
            std::cout << b << "Checkmate! "
                      << (turn == Colour::WHITE ? "Black" : "White") << " wins!\n";
            return 0;
        }
        if (b.isStalemate(turn))
        {
            std::cout << b << "Stalemate!\n";
            return 0;
        }

        Strategy &s = (turn == Colour::WHITE) ? static_cast<Strategy &>(white)
                                              : static_cast<Strategy &>(black);
        b.applyMove(s.chooseMove(b, turn));

        turn = (turn == Colour::WHITE) ? Colour::BLACK : Colour::WHITE;
    }
    std::cout << b << "Stopped after 300 moves (no result).\n";
    return 0;
}