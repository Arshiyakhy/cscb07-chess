#ifndef BOARD_H
#define BOARD_H
#include <array>
#include <memory>
#include "piece.h"
#include "position.h"

class Board {
private:
    std::array<std::array<std::unique_ptr<Piece>, 8>, 8> grid;
public:
    void setupStart();
    Piece* pieceAt(const Position &pos) const;
    void placePiece(std::unique_ptr<Piece> piece, const Position &pos);
    void removePiece(const Position &pos);
};

#endif 