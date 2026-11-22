#ifndef STRATEGY_H
#define STRATEGY_H

#include "board.h"
#include "colour.h"
#include "move.h"

class Strategy
{
public:
    virtual ~Strategy() = default;
    virtual Move chooseMove(Board &b, Colour colour) = 0;
};

#endif