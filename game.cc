#include "game.h"
#include <vector>

namespace
{
    // small helpers only used in this file
    Colour other(Colour c) { return c == Colour::WHITE ? Colour::BLACK : Colour::WHITE; }
    const char *name(Colour c) { return c == Colour::WHITE ? "White" : "Black"; }
}

Game::Game(Board b, std::unique_ptr<Player> w, std::unique_ptr<Player> bl, Colour startTurn)
    : board{std::move(b)}, white{std::move(w)}, black{std::move(bl)}, turn{startTurn} {}

Player &Game::current()
{
    return (turn == Colour::WHITE) ? *white : *black;
}

void Game::playTurn(std::istream &args, std::ostream &out)
{
    if (isOver())
        return;

    // 1. ask the current player what it wants to play
    Move wanted = current().getMove(board, turn, args);

    // 2. is it legal? find the matching move in the legal list
    std::vector<Move> legal = board.legalMoves(turn);
    const Move *chosen = nullptr;
    for (const auto &m : legal)
    {
        if (m == wanted)
        {
            chosen = &m;
            break;
        }
    }
    if (!chosen)
    {
        out << "Invalid move\n";
        return; // same player tries again
    }

    // 3. play the move FROM THE LIST (it has the right type: castle, en passant...)
    board.applyMove(*chosen);
    out << board;

    // 4. other side's turn, then see if the game ended
    turn = other(turn);
    checkGameEnd(out);
}

void Game::checkGameEnd(std::ostream &out)
{
    // 'turn' is now the side that has to move next
    if (board.isCheckmate(turn))
    {
        out << "Checkmate! " << name(other(turn)) << " wins!\n";
        result = (turn == Colour::WHITE) ? Result::BLACK_WINS : Result::WHITE_WINS;
    }
    else if (board.isStalemate(turn))
    {
        out << "Stalemate!\n";
        result = Result::DRAW;
    }
    else if (board.isInCheck(turn))
    {
        out << name(turn) << " is in check.\n";
    }
}

void Game::resign(std::ostream &out)
{
    if (isOver())
        return;
    out << name(other(turn)) << " wins!\n";
    result = (turn == Colour::WHITE) ? Result::BLACK_WINS : Result::WHITE_WINS;
}