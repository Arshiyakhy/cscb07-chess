#include <iostream>
#include <string>
#include "board.h"
#include "pieceFactory.h"
#include "level2.h"
#include "level3.h"

std::string sq(const Position &p)
{
    std::string s;
    s += static_cast<char>('a' + p.col);
    s += static_cast<char>('8' - p.row);
    return s;
}

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
    Level3 l3;

    // ---------- Test 1: don't trade the queen for a defended pawn ----------
    Board a;
    a.placePiece(makePiece('K'), Position::fromString("h1"));
    a.placePiece(makePiece('k'), Position::fromString("h8"));
    a.placePiece(makePiece('Q'), Position::fromString("d1"));
    a.placePiece(makePiece('p'), Position::fromString("d6"));
    a.placePiece(makePiece('p'), Position::fromString("c7")); // defends d6
    std::cout << "Test 1: Qxd6 would lose the queen to cxd6\n"
              << a;
    std::cout << "Level 3's choices (expect NEVER d1 -> d6; likely d1 -> h5 or d1 -> d4, safe checks):\n";
    for (int i = 0; i < 10; ++i)
    {
        Move m = l3.chooseMove(a, Colour::WHITE);
        std::cout << sq(m.from) << " -> " << sq(m.to) << "\n";
    }

    // ---------- Test 2: a good trade, knight for rook ----------
    Board t;
    t.placePiece(makePiece('K'), Position::fromString("h1"));
    t.placePiece(makePiece('k'), Position::fromString("h8"));
    t.placePiece(makePiece('N'), Position::fromString("f3"));
    t.placePiece(makePiece('r'), Position::fromString("e5"));
    t.placePiece(makePiece('p'), Position::fromString("d6")); // defends e5
    std::cout << "\nTest 2: Nxe5 wins a rook (5) for a knight (3)\n"
              << t;
    std::cout << "Level 3's choices (expect f3 -> e5 every time, score +2):\n";
    for (int i = 0; i < 10; ++i)
    {
        Move m = l3.chooseMove(t, Colour::WHITE);
        std::cout << sq(m.from) << " -> " << sq(m.to) << "\n";
    }

    // ---------- Test 3: Level 3 vs Level 2, 20 games ----------
    Level2 l2;
    int l3Wins = 0, l2Wins = 0, none = 0;
    for (int g = 0; g < 20; ++g)
    {
        std::string r = playGame(l3, l2); // Level 3 is white
        if (r == "white")
            ++l3Wins;
        else if (r == "black")
            ++l2Wins;
        else
            ++none;
    }
    std::cout << "\nTest 3: Level 3 (white) vs Level 2 (black), 20 games\n";
    std::cout << "Level 3 wins: " << l3Wins << "\n";
    std::cout << "Level 2 wins: " << l2Wins << "\n";
    std::cout << "No result:    " << none << "\n";

    return 0;
}