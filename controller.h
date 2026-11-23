#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <istream>
#include <ostream>
#include <memory>
#include <string>
#include "board.h"
#include "game.h"
#include "player.h"
#include "scoreBoard.h"

class Controller
{
private:
    std::unique_ptr<Game> game;        // null when no game is running
    ScoreBoard score;

    Board setupBoard;                  // built in setup mode, used by the next game
    bool hasSetup = false;
    Colour setupTurn = Colour::WHITE;

    std::unique_ptr<Player> makePlayer(const std::string &type);
    void startGame(std::istream &args, std::ostream &out);
    void runSetup(std::istream &in, std::ostream &out);
    void finishIfOver();

public:
    void run(std::istream &in, std::ostream &out);
};

#endif