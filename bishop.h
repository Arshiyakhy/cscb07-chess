#ifndef BISHOP_H
#define BISHOP_H
#include "piece.h"
class Bishop: public Piece{
protected:
    char letter() const override;
public:
    explicit Bishop(Colour colour): Piece(colour){}
    int value() const override;
    std::vector<Move> candidateMoves(const Board &b, const Position &from) const override;
};
#endif