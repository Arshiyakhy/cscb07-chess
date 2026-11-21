#include <iostream>
#include "board.h"
#include "pieceFactory.h"
#include "position.h"
#include "colour.h"

int main() {
    std::cout << std::boolalpha;   // print true/false instead of 1/0

    Board b;   // starts empty, no setupStart()
    Position e1 = Position::fromString("e1");
    Position e2 = Position::fromString("e2");
    Position e8 = Position::fromString("e8");

    // Test 1: black rook on e8, white king on e1, nothing between
    b.placePiece(makePiece('r'), e8);
    b.placePiece(makePiece('K'), e1);
    std::cout << b;
    std::cout << "Test 1, e1 attacked by black (expect true): "
              << b.isAttacked(e1, Colour::BLACK) << "\n\n";

    // Test 2: white bishop on e2 blocks the rook
    b.placePiece(makePiece('B'), e2);
    std::cout << b;
    std::cout << "Test 2, e1 attacked by black (expect false): "
              << b.isAttacked(e1, Colour::BLACK) << "\n";

    // Test 3: white never attacks its own king's square
    std::cout << "Test 3, e1 attacked by white (expect false): "
              << b.isAttacked(e1, Colour::WHITE) << "\n\n";

    // Test 4: remove the bishop, the attack comes back
    b.removePiece(e2);
    std::cout << b;
    std::cout << "Test 4, e1 attacked by black (expect true): "
              << b.isAttacked(e1, Colour::BLACK) << "\n";

    return 0;
}