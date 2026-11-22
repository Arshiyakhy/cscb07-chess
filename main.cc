#include <iostream>
#include "board.h"
#include "pieceFactory.h"
#include "position.h"
#include "move.h"

int main() {
    std::cout << std::boolalpha;

    // ---------- Test 1: normal move + undo on the starting board ----------
    Board b;
    b.setupStart();
    Position e2 = Position::fromString("e2");
    Position e4 = Position::fromString("e4");

    std::cout << "Test 1: start\n" << b;

    b.applyMove(Move{e2, e4, MoveType::DOUBLE_PAWN});
    std::cout << "\nAfter e2 -> e4 (pawn should be on e4)\n" << b;

    b.undoMove();
    std::cout << "\nAfter undo (should be the starting board)\n" << b;

    // hasMoved must be false again, or the pawn could never double-step after this
    std::cout << "e2 pawn hasMoved after undo (expect false): "
              << b.pieceAt(e2)->getHasMoved() << "\n";

    // ---------- Test 2: capture + undo ----------
    Board c;
    Position d5 = Position::fromString("d5");
    c.placePiece(makePiece('P'), e4);
    c.placePiece(makePiece('n'), d5);

    std::cout << "\nTest 2: P on e4, n on d5\n" << c;

    c.applyMove(Move{e4, d5});
    std::cout << "\nAfter e4 takes d5 (P on d5, knight gone)\n" << c;

    c.undoMove();
    std::cout << "\nAfter undo (P on e4, n on d5 again)\n" << c;

    // ---------- Test 3: undo with empty history does nothing ----------
    Board d;
    d.undoMove();
    std::cout << "\nTest 3: undo on an empty history didn't crash\n";

    return 0;
}