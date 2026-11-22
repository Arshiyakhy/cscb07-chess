#ifndef PAWN_H
#define PAWN_H
#include "piece.h"
class Pawn: public Piece{
private:
    void addPromotionMoves(std::vector<Move> &moves, const Position &from, const Position &to) const;
protected:
    char letter() const override;
public:
    explicit Pawn(Colour colour): Piece(colour){}
    int value() const override;
    std::vector<Move> candidateMoves(const Board &b, const Position &from) const override;
};
#endif