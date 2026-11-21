#include "king.h"
#include "board.h"

char King::letter() const{return 'K';}
int King::value() const{return 1000;} //a king doesnt really have a value bc the game ends without it so we pick something really big

std::vector<Move> King::candidateMoves(const Board &b, const Position &from) const { 
    std::vector<Move> moves;

    const int dir[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        { 0, -1},{ 0, 1},{ 1, -1}, 
        { 1, 0}, { 1, 1}
    };
    for (const auto &d : dir){
        Position to{from.row + d[0], from.col + d[1]}; //declare the from to here
        if (!to.inBounds()) continue;
        Piece *target = b.pieceAt(to);
        if (target && target->getColour() == getColour()) continue; //same colour
        moves.push_back(Move{from, to});
    }
    return moves;
}