#include "board.h"
#include <string>
#include "pieceFactory.h"
#include <vector>
#include <cctype>

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

bool Board::isAttacked(const Position &pos, Colour byColour)const{
    for(int r=0; r<8; ++r){
        for(int c=0; c<8; ++c){
            Position from{r, c};
            Piece *p = pieceAt(from);
            if (!p || p->getColour() != byColour) continue;
            std::vector<Move> moves = p->candidateMoves(*this,from);
            for(const auto &m : moves){
                if(m.to == pos) return true;
            }
        }
    }
    return false;
}

bool Board::isInCheck(Colour colour)const{
    for(int r=0; r<8; ++r){
        for(int c=0; c<8; ++c){
            Position from{r, c};
            Piece *p = pieceAt(from); 
            if(p && p->getColour()==colour && std::toupper(p->symbol())=='K')return isAttacked(from, colour == Colour::WHITE ? Colour::BLACK : Colour::WHITE);
        }
    }
    return false;
}