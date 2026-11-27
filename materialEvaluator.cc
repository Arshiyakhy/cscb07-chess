#include "materialEvaluator.h"
#include "board.h"

int MaterialEvaluator::evaluate(const Board &b) const
{
    int score = 0;
    for (int r = 0; r < 8; ++r)
    {
        for (int c = 0; c < 8; ++c)
        {
            Piece *target = b.pieceAt(Position{r, c});
            if (!target)
                continue;
            if (target->getColour() == Colour::WHITE)
                score += target->value();
            else
                score -= target->value();
        }
    }
    return score;
}