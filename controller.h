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
#include "textDisplay.h"
#include "colourDisplay.h"

class Controller
{
private:
    std::ostream &out;
    TextDisplay textDisplay;
    ColourDisplay colourDisplay;
    bool useColour;

    std::unique_ptr<Game> game;        // null when no game is running
    ScoreBoard score;

    Board setupBoard;
    bool hasSetup = false;
    Colour setupTurn = Colour::WHITE;

    Observer *activeDisplay();
    std::unique_ptr<Player> makePlayer(const std::string &type);
    void startGame(std::istream &args);
    void runSetup(std::istream &in);
    void switchDisplay(std::istream &args);
    void finishIfOver();

public:
    Controller(std::ostream &out, bool colour)
        : out{out}, textDisplay{out}, colourDisplay{out}, useColour{colour} {}
    void run(std::istream &in);
};

#endif