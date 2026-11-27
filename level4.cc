#include "level4.h"
#include <vector>
#include "board.h"

namespace
{
    const int MATE = 100000; // score for checkmate: much bigger than any material count
    const int INF = 1000000; // "infinity": the starting value for alpha/beta and best scores
}

int Level4::alphaBeta(Board &b, int depthLeft, int alpha, int beta, bool maximizing)
{
    // stopping case 1
    if (depthLeft == 0)
        return evaluator->evaluate(b);
    // whose turn is it on this level? get their legal moves
    Colour colour = (maximizing == true) ? Colour::WHITE : Colour::BLACK;
    std::vector<Move> moves = b.legalMoves(colour);
    // stopping cases 2 and 3
    if (moves.empty())
    {
        // checkmate or stalemate?
        if (b.isInCheck(colour))
        {
            // checkmate: the side to move has lost
            // white mated (max level) → huge negative; black mated (min level) → huge positive
            return maximizing ? -(MATE + depthLeft) : (MATE + depthLeft);
        }
        return 0; // stalemate: a draw
    }
    // otherwise: try every move (max level or min level), recurse, prune
    int best = maximizing ? -INF : INF;
    for (const auto &m : moves)
    {
        b.applyMove(m);
        int score = alphaBeta(b, depthLeft - 1, alpha, beta, !maximizing);
        b.undoMove();
        if (maximizing)
        {
            if (score > best)
                best = score;
            if (alpha < best)
                alpha = best;
        }
        else
        {
            if (score < best)
                best = score;
            if (best < beta)
                beta = best;
        }
        if (alpha >= beta)
            break;
    }
    return best;
}

Move Level4::chooseMove(Board &b, Colour colour)
{
    std::vector<Move> moves = b.legalMoves(colour);
    if (moves.empty())
        return Move{}; // safety: game already over

    bool white = (colour == Colour::WHITE);
    int bestScore = white ? -INF : INF; // white wants high, black wants low
    std::vector<Move> bestMoves;

    for (const auto &m : moves)
    {
        b.applyMove(m);
        // this root move used one level; the opponent moves next
        int score = alphaBeta(b, depth - 1, -INF, INF, !white);
        b.undoMove();

        bool better = white ? (score > bestScore) : (score < bestScore);
        if (better)
        {
            bestScore = score; // new best: start the list over
            bestMoves.clear();
            bestMoves.push_back(m);
        }
        else if (score == bestScore)
        {
            bestMoves.push_back(m); // tie: add it
        }
    }
    return randomFrom(bestMoves); // random among the best, so games vary
}