#include "level1.h"

Move Level1::chooseMove(Board &b, Colour colour)
{
    return randomFrom(b.legalMoves(colour)); // any legal move, at random
}