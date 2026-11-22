#include "level2.h"
#include <vector>

Move Level2::chooseMove(Board &b, Colour colour)
{
    std::vector<Move> good;
    std::vector<Move> moves = b.legalMoves(colour);
    for (const auto &m : moves)
    {
        if (isCapture(b, m) || givesCheck(b, m, colour))
            good.push_back(m);
    }
    return randomFrom(good.empty() ? moves : good);
}