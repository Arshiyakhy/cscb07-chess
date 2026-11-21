#include "queen.h"
#include "board.h"

char Queen::letter() const{return 'Q';}
int Queen::value() const{return 9;} //a queen is worth 9 points

std::vector<Move> Queen::candidateMoves(const Board &b, const Position &from) const {
    std::vector<Move> moves;

    const int dirs[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        { 0, -1},{ 0, 1},{ 1, -1}, { 1, 0}, { 1, 1}
    };

    for (const auto &d : dirs) {
        Position to{from.row + d[0], from.col + d[1]};   // first step in this direction

        while (to.inBounds()) {
            Piece *target = b.pieceAt(to);

            if (!target) {                                // empty: add and keep sliding
                moves.push_back(Move{from, to});
            } else {
                if (target->getColour() != getColour()) { // enemy: capture
                    moves.push_back(Move{from, to});
                }
                break;                                    // any piece stops this direction
            }

            to.row += d[0];                               // next step
            to.col += d[1];
        }
    }
    return moves;
}