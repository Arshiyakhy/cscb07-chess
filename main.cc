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

// print only the castling moves from legalMoves
void printCastles(Board &b, Colour c)
{
    int n = 0;
    for (const auto &m : b.legalMoves(c))
    {
        if (m.type == MoveType::CASTLE)
        {
            std::cout << "  " << sq(m.from) << " -> " << sq(m.to) << "\n";
            ++n;
        }
    }
    if (n == 0)
        std::cout << "  (none)\n";
}

// white K e1, rooks a1 and h1; black king far away on h8
void setupBasic(Board &b)
{
    b.placePiece(makePiece('K'), Position::fromString("e1"));
    b.placePiece(makePiece('R'), Position::fromString("a1"));
    b.placePiece(makePiece('R'), Position::fromString("h1"));
    b.placePiece(makePiece('k'), Position::fromString("h8"));
}

int main()
{
    std::cout << "Test 1: both sides open (expect e1 -> g1 and e1 -> c1)\n";
    Board t1;
    setupBasic(t1);
    printCastles(t1, Colour::WHITE);

    std::cout << "\nTest 2: knight on g1 blocks kingside (expect only e1 -> c1)\n";
    Board t2;
    setupBasic(t2);
    t2.placePiece(makePiece('N'), Position::fromString("g1"));
    printCastles(t2, Colour::WHITE);

    std::cout << "\nTest 3: black rook on f8 attacks f1 (expect only e1 -> c1)\n";
    Board t3;
    setupBasic(t3);
    t3.placePiece(makePiece('r'), Position::fromString("f8"));
    printCastles(t3, Colour::WHITE);

    std::cout << "\nTest 4: white king in check from a rook on e5 (expect none)\n";
    Board t4;
    setupBasic(t4);
    t4.placePiece(makePiece('r'), Position::fromString("e5"));
    printCastles(t4, Colour::WHITE);

    std::cout << "\nTest 5: b1 attacked is still OK for queenside (expect both)\n";
    Board t5;
    setupBasic(t5);
    t5.placePiece(makePiece('r'), Position::fromString("b8"));
    printCastles(t5, Colour::WHITE);

    std::cout << "\nTest 6: king moved away and back (expect none)\n";
    Board t6;
    setupBasic(t6);
    t6.applyMove(Move{Position::fromString("e1"), Position::fromString("e2")});
    t6.applyMove(Move{Position::fromString("h8"), Position::fromString("g8")});
    t6.applyMove(Move{Position::fromString("e2"), Position::fromString("e1")});
    printCastles(t6, Colour::WHITE);

    std::cout << "\nTest 7: apply kingside castle (expect K on g1, R on f1, h1 empty)\n";
    Board t7;
    setupBasic(t7);
    t7.applyMove(Move{Position::fromString("e1"), Position::fromString("g1"), MoveType::CASTLE});
    std::cout << t7;

    std::cout << "Test 7b: undo it (expect K e1, R h1, and both castles available again)\n";
    t7.undoMove();
    std::cout << t7;
    printCastles(t7, Colour::WHITE);

    std::cout << "\nTest 8: apply queenside castle (expect K on c1, R on d1, a1 empty)\n";
    Board t8;
    setupBasic(t8);
    t8.applyMove(Move{Position::fromString("e1"), Position::fromString("c1"), MoveType::CASTLE});
    std::cout << t8;

    std::cout << "Test 9: black can castle too (expect e8 -> g8 and e8 -> c8)\n";
    Board t9;
    t9.placePiece(makePiece('k'), Position::fromString("e8"));
    t9.placePiece(makePiece('r'), Position::fromString("a8"));
    t9.placePiece(makePiece('r'), Position::fromString("h8"));
    t9.placePiece(makePiece('K'), Position::fromString("h1"));
    printCastles(t9, Colour::BLACK);

    return 0;
}