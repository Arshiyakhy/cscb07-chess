#include "controller.h"
#include <sstream>
#include "humanPlayer.h"
#include "computerPlayer.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "pieceFactory.h"

// "human" or "computer1".."computer4" → a Player (nullptr if unknown)
std::unique_ptr<Player> Controller::makePlayer(const std::string &type)
{
    if (type == "human")     return std::make_unique<HumanPlayer>();
    if (type == "computer1") return std::make_unique<ComputerPlayer>(std::make_unique<Level1>());
    if (type == "computer2") return std::make_unique<ComputerPlayer>(std::make_unique<Level2>());
    if (type == "computer3") return std::make_unique<ComputerPlayer>(std::make_unique<Level3>());
    if (type == "computer4") return std::make_unique<ComputerPlayer>(std::make_unique<Level3>()); // TODO: Level4
    return nullptr;
}

void Controller::startGame(std::istream &args, std::ostream &out)
{
    if (game) { out << "A game is already running\n"; return; }

    std::string w, b;
    args >> w >> b;
    auto white = makePlayer(w);
    auto black = makePlayer(b);
    if (!white || !black) { out << "Usage: game <human|computer1-4> <human|computer1-4>\n"; return; }

    Board board;
    Colour turn = Colour::WHITE;
    if (hasSetup)                       // use the position from setup mode
    {
        board = std::move(setupBoard);
        turn = setupTurn;
        hasSetup = false;
    }
    else
    {
        board.setupStart();
    }

    game = std::make_unique<Game>(std::move(board), std::move(white), std::move(black), turn);
    out << game->getBoard();
}

void Controller::runSetup(std::istream &in, std::ostream &out)
{
    if (game) { out << "Can't enter setup during a game\n"; return; }

    setupBoard = Board{};               // start from an empty board
    setupTurn = Colour::WHITE;
    out << setupBoard;

    std::string line;
    while (std::getline(in, line))
    {
        std::istringstream iss{line};
        std::string cmd;
        if (!(iss >> cmd)) continue;    // empty line

        if (cmd == "+")
        {
            std::string piece, sq;
            iss >> piece >> sq;
            Position pos = Position::fromString(sq);
            auto p = piece.size() == 1 ? makePiece(piece[0]) : nullptr;
            if (!p || !pos.inBounds()) { out << "Usage: + <piece> <square>\n"; continue; }
            setupBoard.placePiece(std::move(p), pos);
            out << setupBoard;
        }
        else if (cmd == "-")
        {
            std::string sq;
            iss >> sq;
            Position pos = Position::fromString(sq);
            if (!pos.inBounds()) { out << "Usage: - <square>\n"; continue; }
            setupBoard.removePiece(pos);
            out << setupBoard;
        }
        else if (cmd == "=")
        {
            std::string colour;
            iss >> colour;
            if (colour == "white") setupTurn = Colour::WHITE;
            else if (colour == "black") setupTurn = Colour::BLACK;
            else out << "Usage: = <white|black>\n";
        }
        else if (cmd == "done")
        {
            if (setupBoard.isValidSetup()) { hasSetup = true; return; }
            out << "Invalid setup: need exactly one king each, no pawns on the first or last row, "
                   "and no king in check\n";
        }
        else
        {
            out << "Unknown setup command\n";
        }
    }
}

// if the game just ended, add the points and clear it
void Controller::finishIfOver()
{
    if (game && game->isOver())
    {
        score.record(game->getResult());
        game.reset();
    }
}

void Controller::run(std::istream &in, std::ostream &out)
{
    std::string line;
    while (std::getline(in, line))
    {
        std::istringstream iss{line};
        std::string cmd;
        if (!(iss >> cmd)) continue;    // empty line

        if (cmd == "game")
        {
            startGame(iss, out);
        }
        else if (cmd == "move")
        {
            if (!game) { out << "No game is running\n"; continue; }
            game->playTurn(iss, out);
            finishIfOver();
        }
        else if (cmd == "resign")
        {
            if (!game) { out << "No game is running\n"; continue; }
            game->resign(out);
            finishIfOver();
        }
        else if (cmd == "setup")
        {
            runSetup(in, out);
        }
        else
        {
            out << "Unknown command\n";
        }
    }
    score.print(out);                   // ctrl-D: input ended
}