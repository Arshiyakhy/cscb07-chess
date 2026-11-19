#include "piece.h"
#include <cctype> //returns integer value of a character

char Piece::symbol() const{
    char c = letter();
    if (getColour() == Colour::BLACK) return static_cast<char>(std::tolower(c)); //black pieces have lower case
    return c;
}