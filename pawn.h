#ifndef PAWN_H
#define PAWN_H
#include "piece.h"
class Pawn: public Piece{
protected:
    char letter() const override;
public:
    explicit Pawn(Colour colour): Piece(colour){}
    int value() const override;
    std::vector<Move> candidateMoves(const Board &b, const Position &from) const override;
};
#endif