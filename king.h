#ifndef KING_H
#define KING_H
#include "piece.h"

class King: public Piece{
protected:
    char letter() const override; // for typos to not make a brand new function
public:
    explicit King(Colour colour): Piece(colour) {} //cnstructor takes the colour and passes it 
    int value() const override;
    std::vector<Move> candidateMoves(const Board &b, const Position &from) const override;
};
#endif