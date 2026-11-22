#ifndef STRATEGY_H
#define STRATEGY_H

#include <random>
#include <vector>
#include "board.h"
#include "colour.h"
#include "move.h"

class Strategy
{
private:
    std::mt19937 rng; // one random generator shared by every level

protected:
    // pick a random move from a list (returns Move{} if the list is empty)
    Move randomFrom(const std::vector<Move> &moves);
    bool isCapture(const Board &b, const Move &m);
    bool givesCheck(Board &b, const Move &m, Colour colour);

public:
    Strategy() : rng(std::random_device{}()) {}
    virtual ~Strategy() = default;
    virtual Move chooseMove(Board &b, Colour colour) = 0;
};

#endif