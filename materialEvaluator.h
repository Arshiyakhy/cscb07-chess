#ifndef MATERIALEVALUATOR_H
#define MATERIALEVALUATOR_H

#include "evaluator.h"
class MaterialEvaluator : public Evaluator
{
public:
    int evaluate(const Board &b) const override;
};
#endif