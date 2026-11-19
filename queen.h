#ifndef QUEEN_H
#define QUEEN_H
#include "piece.h"
class Queen: public Piece{
protected:
    char letter() const override;
public:
    explicit Queen(Colour colour): Piece(colour) {}
    int value() const override;
};
#endif