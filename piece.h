#ifndef PIECE_H
#define PIECE_H
#include "position.h"
#include "colour.h"
#include "move.h"
#include <vector>

class Piece{
private:
    bool hasMoved_=false;
    Colour colour_;
protected:
    virtual char letter() const=0; //pure virtual cuz of abstraction
public:
    explicit Piece(Colour colour): //one argument so explicit
    colour_(colour){}
    virtual ~Piece(){} //virtual cause when you need to delete a knight you need to delete that as a knight then a piece
    bool getHasMoved() const{
        return hasMoved_;
    }
    Colour getColour() const{
        return colour_;
    }
    void setHasMoved(bool hasMoved){
        hasMoved_ = hasMoved;
    } 
    char symbol() const;
    virtual int value() const=0; //not protected bc of ai stuff in the future
    class Board; //forward declaration of board class so we can use it in the isValidMove function
    virtual std::vector<Move> candidateMoves(const Board &b, const Position &from) const = 0;

};
#endif