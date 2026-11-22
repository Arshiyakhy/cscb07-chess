#include <iostream>
#include <string>
#include "board.h"
#include "pieceFactory.h"
#include "position.h"
#include "move.h"

// turn a Position into "e2" for printing
std::string sq(const Position &p) {
    std::string s;
    s += static_cast<char>('a' + p.col);
    s += static_cast<char>('8' - p.row);
    return s;
}

void printMoves(const std::vector<Move> &moves) {
    for (const auto &m : moves) {
        std::cout << sq(m.from) << " -> " << sq(m.to) << "\n";
    }
    std::cout << "Total: " << moves.size() << "\n";
}

int main() {
    // ---------- Test 1: pinned bishop ----------
    Board b;
    b.placePiece(makePiece('K'), Position::fromString("e1"));
    b.placePiece(makePiece('B'), Position::fromString("e2"));
    b.placePiece(makePiece('r'), Position::fromString("e8"));

    std::cout << "Test 1: bishop on e2 is pinned by the rook\n" << b;
    std::cout << "Legal moves for white (expect only king moves: d1 f1 d2 f2, total 4):\n";
    printMoves(b.legalMoves(Colour::WHITE));

    // ---------- Test 2: starting position ----------
    Board s;
    s.setupStart();
    std::cout << "\nTest 2: starting position\n";
    std::cout << "Legal moves for white (expect total 20: 16 pawn + 4 knight):\n";
    printMoves(s.legalMoves(Colour::WHITE));

    // ---------- Test 3: the board is unchanged after legalMoves ----------
    std::cout << "\nTest 3: board after calling legalMoves (should still be the start)\n" << s;

    return 0;
}