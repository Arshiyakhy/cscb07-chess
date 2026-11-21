#include "pawn.h"
#include "board.h"

char Pawn::letter() const {return 'P';}
int Pawn::value() const {return 1;}
std::vector<Move> Pawn::candidateMoves(const Board &b, const Position &from) const { 
    std::vector<Move> moves;

    const int jumps[8][2] = {
        {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
        { 1, -2}, { 1, 2}, { 2, -1}, { 2, 1}
    };
    for (const auto &j : jumps){
        Position to{from.row + j[0], from.col + j[1]}; //declare the from to here
        if (!to.inBounds()) continue;
        Piece *target = b.pieceAt(to);
        if (target && target->getColour() == getColour()) continue; //same colour
        moves.push_back(Move{from, to});
    }
    return moves;
}