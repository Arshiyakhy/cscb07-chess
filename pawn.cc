#include "pawn.h"
#include "board.h"
#include <cstdlib>

void Pawn::addPromotionMoves(std::vector<Move> &moves, const Position &from, const Position &to) const {
    const char options[4] = {'Q', 'R', 'B', 'N'};
    for (char p : options) {
        moves.push_back(Move{from, to, MoveType::PROMOTION, p});
    }
}

char Pawn::letter() const {return 'P';}
int Pawn::value() const {return 1;}
std::vector<Move> Pawn::candidateMoves(const Board &b, const Position &from) const { 
    std::vector<Move> moves;
    int dir = (getColour() == Colour::WHITE) ? -1 : 1;
    int startRow = (getColour() == Colour::WHITE) ? 6 : 1;
    int lastRow = (getColour() == Colour::WHITE) ? 0 : 7;
    const Move *last = b.lastMove();
    if (last && last->type == MoveType::DOUBLE_PAWN && last->to.row == from.row && std::abs(last->to.col - from.col) == 1){
        Position en_passant{dir+from.row,last->to.col};
        moves.push_back(Move{from, en_passant, MoveType::EN_PASSANT});
    }
    Position one{dir+from.row, from.col};
    if(one.inBounds() && !b.pieceAt(one)){
        if(one.row == lastRow){
            addPromotionMoves(moves, from, one);
        } else {
        moves.push_back(Move{from, one});
    }
        Position two{from.row + 2*dir, from.col};
        if( from.row == startRow && !b.pieceAt(two)) moves.push_back(Move{from, two, MoveType::DOUBLE_PAWN});
    }
    const int sides[2] = {-1, 1};
    for (int s : sides) {
        Position diag{from.row + dir, from.col + s};
        if (!diag.inBounds()) continue;

        Piece *target = b.pieceAt(diag);
        if (target && target->getColour() != getColour()) {
            if(diag.row == lastRow){
                addPromotionMoves(moves, from, diag);
            } else {
                moves.push_back(Move{from, diag});
            }
        }
    }
    return moves;
}