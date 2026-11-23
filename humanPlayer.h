#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "player.h"

class HumanPlayer : public Player
{
public:
    Move getMove(Board &b, Colour colour, std::istream &args) override;
};

#endif