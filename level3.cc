#include "level3.h"
#include <vector>

int Level3::scoreMove(Board &b, const Move &m, Colour colour)
{
    int score = 0;
    Colour enemy = (colour == Colour::WHITE) ? Colour::BLACK : Colour::WHITE;
    Piece *target = b.pieceAt(m.to);
    if (target)
        score += target->value();
    else if (m.type == MoveType::EN_PASSANT)
        score += 1;
    b.applyMove(m);
    if (b.isAttacked(m.to, enemy))
        score -= b.pieceAt(m.to)->value();
    if (b.isInCheck(enemy))
        score += 1;
    b.undoMove();
    return score;
}

Move Level3::chooseMove(Board &b, Colour colour)
{
    std::vector<Move> moves = b.legalMoves(colour);
    std::vector<Move> bestMoves;
    int best = -1000;
    for (const auto &m : moves)
    {
        int s = scoreMove(b, m, colour);
        if (s > best)
        {
            best = s;
            bestMoves.clear();
            bestMoves.push_back(m);
        }
        else if (s == best)
            bestMoves.push_back(m);
    }
    return randomFrom(bestMoves);
}