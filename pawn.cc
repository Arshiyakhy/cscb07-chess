#include "pawn.h"
#include "board.h"

char Pawn::letter() const {return 'P';}
int Pawn::value() const {return 1;}
std::vector<Move> Pawn::candidateMoves(const Board &b, const Position &from) const { 
    std::vector<Move> moves;
    int dir = (getColour() == Colour::WHITE) ? -1 : 1;
    int startRow = (getColour() == Colour::WHITE) ? 6 : 1;
    Position one{dir+from.row, from.col};
    if(one.inBounds() && !b.pieceAt(one)){
        moves.push_back(Move{from, one});
        Position two{from.row + 2*dir, from.col};
        if( from.row == startRow && !b.pieceAt(two)) moves.push_back(Move{from, two, MoveType::DOUBLE_PAWN});
    }
    const int sides[2] = {-1, 1};
    for (int s : sides) {
        Position diag{from.row + dir, from.col + s};
        if (!diag.inBounds()) continue;

        Piece *target = b.pieceAt(diag);
        if (target && target->getColour() != getColour()) {
            moves.push_back(Move{from, diag});
        }
    }
    return moves;
}