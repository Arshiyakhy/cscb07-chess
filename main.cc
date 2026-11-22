#include <iostream>
#include "board.h"
#include "pieceFactory.h"
#include "position.h"

int main() {
    std::cout << std::boolalpha;

    // ---------- Checkmate: back-rank mate ----------
    Board m;
    m.placePiece(makePiece('K'), Position::fromString("g1"));
    m.placePiece(makePiece('P'), Position::fromString("f2"));
    m.placePiece(makePiece('P'), Position::fromString("g2"));
    m.placePiece(makePiece('P'), Position::fromString("h2"));
    m.placePiece(makePiece('r'), Position::fromString("a1"));
    std::cout << "Back-rank mate\n" << m;
    std::cout << "white checkmate (expect true): " << m.isCheckmate(Colour::WHITE) << "\n";
    std::cout << "white stalemate (expect false): " << m.isStalemate(Colour::WHITE) << "\n\n";

    // ---------- Stalemate: black king trapped but not in check ----------
    Board s;
    s.placePiece(makePiece('k'), Position::fromString("h8"));
    s.placePiece(makePiece('Q'), Position::fromString("g6"));
    s.placePiece(makePiece('K'), Position::fromString("f7"));
    std::cout << "Stalemate\n" << s;
    std::cout << "black checkmate (expect false): " << s.isCheckmate(Colour::BLACK) << "\n";
    std::cout << "black stalemate (expect true): " << s.isStalemate(Colour::BLACK) << "\n\n";

    // ---------- Neither: starting position ----------
    Board n;
    n.setupStart();
    std::cout << "Start: white checkmate (expect false): " << n.isCheckmate(Colour::WHITE) << "\n";
    std::cout << "Start: white stalemate (expect false): " << n.isStalemate(Colour::WHITE) << "\n";

    return 0;
}