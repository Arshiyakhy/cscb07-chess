#ifndef QUEEN_H
#define QUEEN_H
#include "piece.h"
class Queen: public Piece{
protected:
    char letter() const override;
public:
    explicit Queen(Colour colour): Piece(colour) {}
    int value() const override;
    std::vector<Move> candidateMoves(const Board &b, const Position &from) const override;
};
#endif