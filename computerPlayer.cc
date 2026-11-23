#include "computerPlayer.h"

Move ComputerPlayer::getMove(Board &b, Colour colour, std::istream &)
{
    return strategy->chooseMove(b, colour); // the plain "move" command has no args
}