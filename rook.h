#ifndef ROOK_H
#define ROOK_H
#include "piece.h"
class Rook: public Piece{
protected:
    char letter() const override;
public:
    explicit Rook(Colour colour): Piece(colour){}
    int value() const override;
    std::vector<Move> candidateMoves(const Board &b, const Position &from) const override;
};
#endif