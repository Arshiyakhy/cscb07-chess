#include "rook.h"
#include "board.h"

char Rook::letter() const { return 'R'; }
int Rook::value() const { return 5; }

std::vector<Move> Rook::candidateMoves(const Board &b, const Position &from) const {
    std::vector<Move> moves;

    const int dirs[4][2] = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}
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