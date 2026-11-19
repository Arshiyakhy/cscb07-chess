#include "position.h"

//check if position is in bounds of the chess board
bool Position::inBounds() const {
    return row<=7 && row>=0 && col>=0 && col<=7;
}

//check if two positions are equal
bool Position::operator==(const Position &other) const{
    return other.row == row && other.col == col;
}

//get position based on string representation of position
Position Position::fromString(const std::string &str){
    //the spec says they will use lower case so we dont need to check for that
    if (str.length() != 2) return Position(-1, -1); //check for valid length
    int row = 8 - (str[1] - '0');
    int col = str[0] - 'a';
    if (!Position(row, col).inBounds()) return Position(-1, -1); //check for valid position
    return Position(row, col);
}