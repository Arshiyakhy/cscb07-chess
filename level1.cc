#include "level1.h"

Move Level1::chooseMove(Board &b, Colour colour)
{
    std::vector<Move> moves = b.legalMoves(colour);
    if (moves.empty())
        return Move{}; // no legal moves, return a default move

    std::uniform_int_distribution<std::size_t> dist(0, moves.size() - 1);
    return moves[dist(rng)];
}