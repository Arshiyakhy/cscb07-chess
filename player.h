#ifndef PLAYER_H
#define PLAYER_H

#include <istream>
#include "board.h"
#include "colour.h"
#include "move.h"

class Player
{
public:
    virtual ~Player() = default;

    // the move this player wants to make.
    // 'args' is the rest of the command line (e.g. "e2 e4" or "e7 e8 Q").
    // returns Move{} (invalid squares) if the input can't be understood.
    virtual Move getMove(Board &b, Colour colour, std::istream &args) = 0;
};

#endif