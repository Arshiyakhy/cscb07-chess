#include "strategy.h"

Move Strategy::randomFrom(const std::vector<Move> &moves)
{
    if (moves.empty())
        return Move{};

    std::uniform_int_distribution<std::size_t> dist(0, moves.size() - 1);
    return moves[dist(rng)];
}