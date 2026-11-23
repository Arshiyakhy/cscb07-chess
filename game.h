#ifndef GAME_H
#define GAME_H

#include <istream>
#include <ostream>
#include <memory>
#include "board.h"
#include "player.h"
#include "colour.h"
#include "subject.h"

enum class Result
{
    ONGOING,
    WHITE_WINS,
    BLACK_WINS,
    DRAW
};

class Game : public Subject
{
private:
    Board board;
    std::unique_ptr<Player> white;
    std::unique_ptr<Player> black;
    Colour turn;
    Result result = Result::ONGOING;

    Player &current();                    // the player whose turn it is
    void checkGameEnd(std::ostream &out); // after a move: mate / stalemate / check

public:
    Game(Board b, std::unique_ptr<Player> w, std::unique_ptr<Player> bl, Colour startTurn);

    void playTurn(std::istream &args, std::ostream &out); // one "move" command
    void resign(std::ostream &out);
    bool isOver() const { return result != Result::ONGOING; }
    Result getResult() const { return result; }
    const Board &getBoard() const { return board; }
    void display() const { notifyObservers(board); }
};

#endif