#ifndef KNIGHT_H
#define KNIGHT_H
#include "piece.h"
class Knight: public Piece{
protected:
    char letter() const override;
public:
    explicit Knight(Colour colour): Piece(colour){}
    int value() const override;
};
#endif