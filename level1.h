#ifndef LEVEL1_H
#define LEVEL1_H

#include "strategy.h"

class Level1 : public Strategy
{
public:
    Move chooseMove(Board &b, Colour colour) override;
};

#endif