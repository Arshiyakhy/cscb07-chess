#ifndef LEVEL1_H
#define LEVEL1_H

#include <random>
#include "strategy.h"

class Level1 : public Strategy
{

private:
    std::mt19937 rng; // random number generator

public:
    Level1() : rng(std::random_device{}()) {} // initialize rng with a random
    Move chooseMove(Board &b, Colour colour) override;
};

#endif