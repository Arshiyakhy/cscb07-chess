#ifndef LEVEL2_H
#define LEVEL2_H

#include "strategy.h"

class Level2 : public Strategy
{
public:
    Move chooseMove(Board &b, Colour colour) override;
};

#endif