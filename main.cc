#include <iostream>
#include <string>
#include "position.h"
#include "colour.h"
#include "piece.h"
#include "king.h"
#include "queen.h"
#include "bishop.h"
#include "knight.h"
#include "pawn.h"
#include "rook.h"
#include <memory>
#include <vector>
#include "board.h"
#include "pieceFactory.h"
using namespace std;

int main(){
//     King king(Colour::WHITE);
//     cout << "King symbol: " << king.symbol() << std::endl;
//     cout << "King value: " << king.value() << std::endl;
//     King blackKing(Colour::BLACK);
//     cout << "Black King symbol: " << blackKing.symbol() << std::endl;
//     cout << "Black King value: " << blackKing.value() << std::endl;
//     Queen queen(Colour::WHITE);
//     cout << "Queen symbol: " << queen.symbol() << std::endl;
//     cout << "Queen value: " << queen.value() << std::endl;
//     Bishop bishop(Colour::WHITE);
//     cout << "Bishop symbol: " << bishop.symbol() << std::endl;
//     cout << "Bishop value: " << bishop.value() << std::endl;
//     Knight knight(Colour::WHITE);
//     cout << "Knight symbol: " << knight.symbol() << std::endl;
//     cout << "Knight value: " << knight.value() << std::endl;
//     Pawn pawn(Colour::WHITE);
//     cout << "Pawn symbol: " << pawn.symbol() << std::endl;
//     cout << "Pawn value: " << pawn.value() << std::endl;
//     Rook rook(Colour::WHITE);
//     cout << "Rook symbol: " << rook.symbol() << std::endl;
//     cout << "Rook value: " << rook.value() << std::endl;
//     Queen blackQueen(Colour::BLACK);
//     cout << "Black Queen symbol: " << blackQueen.symbol() << std::endl;
//     cout << "Black Queen value: " << blackQueen.value() << std::endl;
//     Bishop blackBishop(Colour::BLACK);
//     cout << "Black Bishop symbol: " << blackBishop.symbol() << std::endl;
//     cout << "Black Bishop value: " << blackBishop.value() << std::endl;
//     Knight blackKnight(Colour::BLACK);
//     cout << "Black Knight symbol: " << blackKnight.symbol() << std::endl;
//     cout << "Black Knight value: " << blackKnight.value() << std::endl;
//     Pawn blackPawn(Colour::BLACK);
//     cout << "Black Pawn symbol: " << blackPawn.symbol() << std::endl;
//     cout << "Black Pawn value: " << blackPawn.value() << std::endl;
//     Rook blackRook(Colour::BLACK);
//     cout << "Black Rook symbol: " << blackRook.symbol() << std::endl;
//     cout << "Black Rook value: " << blackRook.value() << std::endl;
//     std::vector<std::unique_ptr<Piece>> pieces;
// pieces.push_back(std::make_unique<King>(Colour::WHITE));
// pieces.push_back(std::make_unique<Knight>(Colour::BLACK));

// for (const auto &p : pieces) {
//     std::cout << p->symbol() << " " << p->value() << "\n";
// }
    Board b;
    b.setupStart();
    Piece *p = b.pieceAt(Position::fromString("e2"));
if (p) std::cout << p->symbol() << "\n";      // P

p = b.pieceAt(Position::fromString("e8"));
if (p) std::cout << p->symbol() << "\n";      // k

p = b.pieceAt(Position::fromString("e4"));
std::cout << (p ? "piece" : "empty") << "\n"; // empty

b.placePiece(makePiece('Q'), Position::fromString("e4"));
std::cout << b.pieceAt(Position::fromString("e4"))->symbol() << "\n";  // Q

b.removePiece(Position::fromString("e4"));
std::cout << (b.pieceAt(Position::fromString("e4")) ? "piece" : "empty") << "\n"; // empty
std::cout << b;
    return 0;
}