#include "strategy.h"

Move Strategy::randomFrom(const std::vector<Move> &moves)
{
    if (moves.empty())
        return Move{};

    std::uniform_int_distribution<std::size_t> dist(0, moves.size() - 1);
    return moves[dist(rng)];
}

// true if this move takes an enemy piece
bool Strategy::isCapture(const Board &b, const Move &m)
{
    // normal capture: something is standing on the target square
    if (b.pieceAt(m.to) != nullptr)
        return true;
    // en passant: the target square is empty, but a pawn still gets taken
    return m.type == MoveType::EN_PASSANT;
}

// true if this move puts the opponent's king in check
// 'colour' = the side MAKING the move
bool Strategy::givesCheck(Board &b, const Move &m, Colour colour)
{
    Colour enemy = (colour == Colour::WHITE) ? Colour::BLACK : Colour::WHITE;

    b.applyMove(m);                  // try the move
    bool check = b.isInCheck(enemy); // is the enemy king attacked now?
    b.undoMove();                    // put the board back exactly as it was

    return check;
}