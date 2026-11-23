#include <iostream>
#include "board.h"
#include "pieceFactory.h"
#include "position.h"

int main()
{
    std::cout << std::boolalpha;

    // ---------- pawn attacks on empty squares ----------
    Board b;
    b.placePiece(makePiece('p'), Position::fromString("e2"));
    std::cout << b;
    std::cout << "f1 attacked by black (expect true):  " << b.isAttacked(Position::fromString("f1"), Colour::BLACK) << "\n";
    std::cout << "d1 attacked by black (expect true):  " << b.isAttacked(Position::fromString("d1"), Colour::BLACK) << "\n";
    std::cout << "e1 attacked by black (expect false): " << b.isAttacked(Position::fromString("e1"), Colour::BLACK) << "\n";

    // white pawn attacks upward
    Board w;
    w.placePiece(makePiece('P'), Position::fromString("d4"));
    std::cout << "c5 attacked by white (expect true):  " << w.isAttacked(Position::fromString("c5"), Colour::WHITE) << "\n";
    std::cout << "d5 attacked by white (expect false): " << w.isAttacked(Position::fromString("d5"), Colour::WHITE) << "\n";
    std::cout << "c3 attacked by white (expect false): " << w.isAttacked(Position::fromString("c3"), Colour::WHITE) << "\n";

    // ---------- regression: nothing else broke ----------
    Board s;
    s.setupStart();
    std::cout << "start position legal moves (expect 20): " << s.legalMoves(Colour::WHITE).size() << "\n";

    Board m;
    m.placePiece(makePiece('K'), Position::fromString("g1"));
    m.placePiece(makePiece('P'), Position::fromString("f2"));
    m.placePiece(makePiece('P'), Position::fromString("g2"));
    m.placePiece(makePiece('P'), Position::fromString("h2"));
    m.placePiece(makePiece('r'), Position::fromString("a1"));
    std::cout << "back-rank mate (expect true): " << m.isCheckmate(Colour::WHITE) << "\n";

    return 0;
}