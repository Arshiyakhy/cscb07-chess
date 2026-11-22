#include <iostream>
#include <string>
#include "board.h"
#include "pieceFactory.h"
#include "position.h"
#include "move.h"

std::string sq(const Position &p)
{
    std::string s;
    s += static_cast<char>('a' + p.col);
    s += static_cast<char>('8' - p.row);
    return s;
}

int main()
{
    Position e5 = Position::fromString("e5");
    Position d7 = Position::fromString("d7");
    Position d5 = Position::fromString("d5");
    Position d6 = Position::fromString("d6");

    // ---------- Test 1: en passant is generated ----------
    Board b;
    b.placePiece(makePiece('K'), Position::fromString("a1"));
    b.placePiece(makePiece('k'), Position::fromString("h8"));
    b.placePiece(makePiece('P'), e5);
    b.placePiece(makePiece('p'), d7);

    b.applyMove(Move{d7, d5, MoveType::DOUBLE_PAWN}); // black double-steps next to the white pawn
    std::cout << "Test 1: black just played d7 -> d5\n"
              << b;

    std::cout << "White's en passant moves (expect e5 -> d6):\n";
    for (const auto &m : b.legalMoves(Colour::WHITE))
    {
        if (m.type == MoveType::EN_PASSANT)
        {
            std::cout << sq(m.from) << " -> " << sq(m.to) << "\n";
        }
    }

    // ---------- Test 2: apply en passant ----------
    b.applyMove(Move{e5, d6, MoveType::EN_PASSANT});
    std::cout << "\nTest 2: after e5 takes d6 en passant (expect P on d6, d5 EMPTY)\n"
              << b;

    // ---------- Test 3: undo en passant ----------
    b.undoMove();
    std::cout << "\nTest 3: after undo (expect P on e5 and p back on d5, d6 empty)\n"
              << b;

    // ---------- Test 4: not available if the pawn is far away ----------
    Board f;
    f.placePiece(makePiece('K'), Position::fromString("a1"));
    f.placePiece(makePiece('k'), Position::fromString("h8"));
    f.placePiece(makePiece('P'), Position::fromString("h5"));
    f.placePiece(makePiece('p'), Position::fromString("a7"));
    f.applyMove(Move{Position::fromString("a7"), Position::fromString("a5"), MoveType::DOUBLE_PAWN});
    int count = 0;
    for (const auto &m : f.legalMoves(Colour::WHITE))
    {
        if (m.type == MoveType::EN_PASSANT)
            ++count;
    }
    std::cout << "\nTest 4: en passant moves when the pawns are far apart (expect 0): " << count << "\n";

    // ---------- Test 5: normal capture undo still works ----------
    Board c;
    Position e4 = Position::fromString("e4");
    c.placePiece(makePiece('P'), e4);
    c.placePiece(makePiece('n'), d5);
    c.applyMove(Move{e4, d5});
    c.undoMove();
    std::cout << "\nTest 5: normal capture then undo (expect P on e4, n on d5)\n"
              << c;

    return 0;
}