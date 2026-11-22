#ifndef LEVEL3_H
#define LEVEL3_H

#include "strategy.h"

class Level3 : public Strategy
{
private:
    int scoreMove(Board &b, const Move &m, Colour colour);

public:
    Move chooseMove(Board &b, Colour colour) override;
};

#endif