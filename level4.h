#ifndef LEVEL4_H
#define LEVEL4_H

#include "strategy.h"
#include <memory>
#include "evaluator.h"

class Level4 : public Strategy
{
private:
    std::unique_ptr<Evaluator> evaluator;
    int depth;
    int alphaBeta(Board &b, int depthLeft, int alpha, int beta, bool maximizing);

public:
    Level4(std::unique_ptr<Evaluator> e, int d) : evaluator(std::move(e)), depth(d)
    {
    }
    Move chooseMove(Board &b, Colour colour) override;
};

#endif