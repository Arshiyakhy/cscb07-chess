#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <ostream>
#include "game.h"

class ScoreBoard
{
private:
    double white = 0;
    double black = 0;

public:
    void record(Result r); // add points for a finished game
    void print(std::ostream &out) const;
};

#endif