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

void Board::applyMove(const Move &m) {
    if (!m.from.inBounds() || !m.to.inBounds()) return;   // invalid squares

    auto &fromCell = grid[m.from.row][m.from.col];
    auto &toCell   = grid[m.to.row][m.to.col];
    if (!fromCell) return;                                 // nothing to move

    UndoInfo info;
    info.move = m;
    info.movedBefore = fromCell->getHasMoved();            // BEFORE moving it
    info.capturedPiece = std::move(toCell);                // take the captured piece out first

    toCell = std::move(fromCell);                          // move the piece
    toCell->setHasMoved(true);                             // the piece is in toCell now

    // promotion: swap the pawn on 'to' for the chosen piece
    if (m.type == MoveType::PROMOTION) {
        info.promotedPawn = std::move(toCell);                     // keep the original pawn
        char letter = m.promotion;                                 // 'Q', 'R', 'B' or 'N'
        if (info.promotedPawn->getColour() == Colour::BLACK) {
            letter = static_cast<char>(std::tolower(static_cast<unsigned char>(letter)));
        }
        toCell = makePiece(letter);                                // new piece on 'to'
        toCell->setHasMoved(true);
    }
    history.push_back(std::move(info));                    // save for undo
}

void Board::undoMove() {
    if (history.empty()) return;                          // nothing to undo

    UndoInfo info = std::move(history.back());            // take the last entry out
    history.pop_back();                                   // then remove its empty slot

    auto &fromCell = grid[info.move.from.row][info.move.from.col];
    auto &toCell   = grid[info.move.to.row][info.move.to.col];

    // promotion: put the original pawn back on 'to' (the queen gets deleted)
    if (info.move.type == MoveType::PROMOTION) {
        toCell = std::move(info.promotedPawn);
    }

    fromCell = std::move(toCell);                         // piece goes back to 'from'
    fromCell->setHasMoved(info.movedBefore);              // restore its old flag
    toCell = std::move(info.capturedPiece);               // captured piece back (or empty)
}

std::vector<Move> Board::legalMoves(Colour colour){
    std::vector<Move> result;
    for(int r=0; r<8; ++r){
        for(int c=0; c<8; ++c){
            Position from{r, c};
            Piece *p = pieceAt(from); 
            if(p && p->getColour()==colour){
                std::vector<Move> moves = p->candidateMoves(*this,from);
                for(const auto &m:moves){
                    applyMove(m);
                    if(!isInCheck(colour)) result.push_back(m);
                    undoMove();
                }
            }
        }
    } 
    return result;   
}

bool Board::isCheckmate(Colour colour){
    return isInCheck(colour) && legalMoves(colour).empty();
}

bool Board::isStalemate(Colour colour){
    return !isInCheck(colour) && legalMoves(colour).empty();
}

const Move* Board::lastMove() const{
    if(history.empty()) return nullptr;
    return &history.back().move;
}