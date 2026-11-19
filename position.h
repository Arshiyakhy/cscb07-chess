#ifndef POSITION_H
#define POSITION_H
#include <string>

// Board coordinate convention (used everywhere in the project):
//
//   row 0 is rank 8 (black's back rank, top of the printed board)
//   row 7 is rank 1 (white's back rank, bottom of the printed board)
//   col 0 is file a, col 7 is file h
//
//        a  b  c  d  e  f  g  h
//        0  1  2  3  4  5  6  7   <- col
//   8    0                        <- row 0
//   7    1
//   6    2
//   5    3
//   4    4
//   3    5
//   2    6
//   1    7                        <- row 7
//
// Examples: "a8" = (0, 0), "h1" = (7, 7), "e2" = (6, 4), "e4" = (4, 4)
//
// So board[row][col] matches the order the board is printed in.
// An invalid Position is (-1, -1); check with inBounds() before using one.
struct Position {
    int row;
    int col;
    Position(int r=-1, int c=-1): row(r), col(c) {}
    bool inBounds() const; //check if position is in bounds of the chess board
    bool operator==(const Position &other) const; //check if two positions are equal
    static Position fromString(const std::string &str);//get position based on string representation of position we use static because we want to call this function without having a position object
};

#endif