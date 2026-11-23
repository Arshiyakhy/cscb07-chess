#include "scoreBoard.h"

void ScoreBoard::record(Result r)
{
    if (r == Result::WHITE_WINS)
        white += 1;
    else if (r == Result::BLACK_WINS)
        black += 1;
    else if (r == Result::DRAW)
    {
        white += 0.5;
        black += 0.5;
    }
}

void ScoreBoard::print(std::ostream &out) const
{
    out << "Final Score:\n";
    out << "White: " << white << "\n";
    out << "Black: " << black << "\n";
}