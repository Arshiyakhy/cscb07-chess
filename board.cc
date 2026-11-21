#include "board.h"
#include <string>
#include "pieceFactory.h"

void Board::setupStart(){
    const std::array<std::string, 8>layout = {
        "rnbqkbnr",   // row 0 = rank 8
        "pppppppp",
        "........",
        "........",
        "........",
        "........",
        "PPPPPPPP",
        "RNBQKBNR"    // row 7 = rank 1
    };
    for(int r=0; r<8; ++r){
        for(int c=0; c<8; ++c){
            grid[r][c] = makePiece(layout[r][c]);
        }
    }
}

Piece* Board::pieceAt(const Position &pos) const{
    if(!pos.inBounds()) return nullptr;
    return grid[pos.row][pos.col].get();
}

void Board::placePiece(std::unique_ptr<Piece> piece, const Position &pos){
    if(!pos.inBounds()) return;
    grid[pos.row][pos.col] = std::move(piece);
}

void Board::removePiece(const Position &pos){
    if(!pos.inBounds()) return;
    grid[pos.row][pos.col] = nullptr;
}

std::ostream &operator<<(std::ostream &out, const Board &b){
    for(int r=0; r<8; ++r){
        out<<8-r<<' ';
        for(int c=0; c<8; ++c){
            if(b.grid[r][c]) out<< b.grid[r][c]->symbol();
            else {
                if((c+r)%2 == 0) out<< ' ';
                else out<< '_';
            }
        }
        out<< "\n";
    }
    out<<"\n"<<"  "<<"abcdefgh"<< "\n";
    return out;
}
