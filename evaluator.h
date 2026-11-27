#ifndef EVALUATOR_H
#define EVALUATOR_H

class Board;
class Evaluator
{
public:
    virtual int evaluate(const Board &b) const = 0; // =0 means pure virtual 
    virtual ~Evaluator() = default;
};
#endif