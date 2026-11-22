#include <iostream>
#include "board.h"
#include "pieceFactory.h"
#include "position.h"
#include "move.h"

int main() {
    Position e7 = Position::fromString("e7");
    Position e8 = Position::fromString("e8");

    // ---------- Test 1: white pawn promotes to a queen, then undo ----------
    Board w;
    w.placePiece(makePiece('K'), Position::fromString("a1"));
    w.placePiece(makePiece('k'), Position::fromString("h8"));
    w.placePiece(makePiece('P'), e7);
    std::cout << "Test 1: before (P on e7)\n" << w;

    w.applyMove(Move{e7, e8, MoveType::PROMOTION, 'Q'});
    std::cout << "\nAfter e7 -> e8 = Q (expect Q on e8, e7 empty)\n" << w;

    w.undoMove();
    std::cout << "\nAfter undo (expect P back on e7, e8 empty)\n" << w;

    // ---------- Test 2: legalMoves lists all 4 choices ----------
    std::cout << "\nTest 2: promotion options for the e7 pawn (expect Q R B N)\n";
    for (const auto &m : w.legalMoves(Colour::WHITE)) {
        if (m.type == MoveType::PROMOTION) {
            std::cout << "promo option: " << m.promotion << "\n";
        }
    }

    // ---------- Test 3: black pawn promotes, should be lowercase ----------
    Board b;
    b.placePiece(makePiece('K'), Position::fromString("h3"));
    b.placePiece(makePiece('k'), Position::fromString("a8"));
    b.placePiece(makePiece('p'), Position::fromString("d2"));
    std::cout << "\nTest 3: before (p on d2)\n" << b;

    b.applyMove(Move{Position::fromString("d2"), Position::fromString("d1"),
                     MoveType::PROMOTION, 'Q'});
    std::cout << "\nAfter d2 -> d1 = Q (expect lowercase q on d1)\n" << b;

    b.undoMove();
    std::cout << "\nAfter undo (expect p back on d2)\n" << b;

    // ---------- Test 4: capture + promotion, then undo ----------
    Board c;
    c.placePiece(makePiece('K'), Position::fromString("a1"));
    c.placePiece(makePiece('k'), Position::fromString("a8"));
    c.placePiece(makePiece('P'), Position::fromString("g7"));
    c.placePiece(makePiece('r'), Position::fromString("h8"));
    std::cout << "\nTest 4: before (P on g7, r on h8)\n" << c;

    c.applyMove(Move{Position::fromString("g7"), Position::fromString("h8"),
                     MoveType::PROMOTION, 'N'});
    std::cout << "\nAfter g7 takes h8 = N (expect N on h8, rook gone)\n" << c;

    c.undoMove();
    std::cout << "\nAfter undo (expect P on g7 AND r back on h8)\n" << c;

    return 0;
}