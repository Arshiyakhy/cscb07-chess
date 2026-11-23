#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include <memory>
#include "player.h"
#include "strategy.h"

class ComputerPlayer : public Player
{
private:
    std::unique_ptr<Strategy> strategy; // Level1, Level2, Level3 (later Level4)

public:
    explicit ComputerPlayer(std::unique_ptr<Strategy> s) : strategy(std::move(s)) {}
    Move getMove(Board &b, Colour colour, std::istream &args) override;
};

#endif