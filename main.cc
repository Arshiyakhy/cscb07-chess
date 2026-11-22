#include <iostream>
#include <string>
#include "board.h"
#include "pieceFactory.h"
#include "level1.h"
#include "level2.h"

std::string sq(const Position &p)
{
    std::string s;
    s += static_cast<char>('a' + p.col);
    s += static_cast<char>('8' - p.row);
    return s;
}

// plays one game, returns "white", "black" or "none"
std::string playGame(Strategy &white, Strategy &black)
{
    Board b;
    b.setupStart();
    Colour turn = Colour::WHITE;
    for (int ply = 0; ply < 300; ++ply)
    {
        if (b.isCheckmate(turn))
            return turn == Colour::WHITE ? "black" : "white";
        if (b.isStalemate(turn))
            return "none";
        Strategy &s = (turn == Colour::WHITE) ? white : black;
        b.applyMove(s.chooseMove(b, turn));
        turn = (turn == Colour::WHITE) ? Colour::BLACK : Colour::WHITE;
    }
    return "none";
}

int main()
{
    // ---------- Test 1: Level 2 always takes the free queen ----------
    Board t;
    t.placePiece(makePiece('K'), Position::fromString("h1"));
    t.placePiece(makePiece('k'), Position::fromString("h8"));
    t.placePiece(makePiece('R'), Position::fromString("a1"));
    t.placePiece(makePiece('q'), Position::fromString("a5"));
    std::cout << "Test 1: white rook a1 can take the black queen on a5\n"
              << t;

    Level2 l2;
    std::cout << "Level 2's choice, 10 tries (expect a1 -> a5 every time):\n";
    for (int i = 0; i < 10; ++i)
    {
        Move m = l2.chooseMove(t, Colour::WHITE);
        std::cout << sq(m.from) << " -> " << sq(m.to) << "\n";
    }

    // ---------- Test 2: Level 2 vs Level 1, 20 games ----------
    Level1 l1;
    int l2Wins = 0, l1Wins = 0, draws = 0;
    for (int g = 0; g < 20; ++g)
    {
        std::string r = playGame(l2, l1); // Level 2 is white
        if (r == "white")
            ++l2Wins;
        else if (r == "black")
            ++l1Wins;
        else
            ++draws;
    }
    std::cout << "\nTest 2: Level 2 (white) vs Level 1 (black), 20 games\n";
    std::cout << "Level 2 wins: " << l2Wins << "\n";
    std::cout << "Level 1 wins: " << l1Wins << "\n";
    std::cout << "No result:    " << draws << "\n";

    return 0;
}