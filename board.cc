#include "board.h"
#include <string>
#include "pieceFactory.h"
#include <vector>
#include <cctype>

void Board::setupStart()
{
    const std::array<std::string, 8> layout = {
        "rnbqkbnr", // row 0 = rank 8
        "pppppppp",
        "........",
        "........",
        "........",
        "........",
        "PPPPPPPP",
        "RNBQKBNR" // row 7 = rank 1
    };
    for (int r = 0; r < 8; ++r)
    {
        for (int c = 0; c < 8; ++c)
        {
            grid[r][c] = makePiece(layout[r][c]);
        }
    }
}

Piece *Board::pieceAt(const Position &pos) const
{
    if (!pos.inBounds())
        return nullptr;
    return grid[pos.row][pos.col].get();
}

void Board::placePiece(std::unique_ptr<Piece> piece, const Position &pos)
{
    if (!pos.inBounds())
        return;
    grid[pos.row][pos.col] = std::move(piece);
}

void Board::removePiece(const Position &pos)
{
    if (!pos.inBounds())
        return;
    grid[pos.row][pos.col] = nullptr;
}

std::ostream &operator<<(std::ostream &out, const Board &b)
{
    for (int r = 0; r < 8; ++r)
    {
        out << 8 - r << ' ';
        for (int c = 0; c < 8; ++c)
        {
            if (b.grid[r][c])
                out << b.grid[r][c]->symbol();
            else
            {
                if ((c + r) % 2 == 0)
                    out << ' ';
                else
                    out << '_';
            }
        }
        out << "\n";
    }
    out << "\n"
        << "  " << "abcdefgh" << "\n";
    return out;
}

bool Board::isAttacked(const Position &pos, Colour byColour) const
{
    for (int r = 0; r < 8; ++r)
    {
        for (int c = 0; c < 8; ++c)
        {
            Position from{r, c};
            Piece *p = pieceAt(from);
            if (!p || p->getColour() != byColour)
                continue;
            // pawns: check their two diagonal squares directly,
            // because their candidate moves only include diagonals with a piece on them
            if (std::toupper(p->symbol()) == 'P')
            {
                int dir = (p->getColour() == Colour::WHITE) ? -1 : 1;
                if (pos.row == r + dir && (pos.col == c - 1 || pos.col == c + 1))
                    return true;
                continue; // a pawn never attacks any other square
            }
            std::vector<Move> moves = p->candidateMoves(*this, from);
            for (const auto &m : moves)
            {
                if (m.to == pos)
                    return true;
            }
        }
    }
    return false;
}

bool Board::isInCheck(Colour colour) const
{
    for (int r = 0; r < 8; ++r)
    {
        for (int c = 0; c < 8; ++c)
        {
            Position from{r, c};
            Piece *p = pieceAt(from);
            if (p && p->getColour() == colour && std::toupper(p->symbol()) == 'K')
                return isAttacked(from, colour == Colour::WHITE ? Colour::BLACK : Colour::WHITE);
        }
    }
    return false;
}

void Board::applyMove(const Move &m)
{
    if (!m.from.inBounds() || !m.to.inBounds())
        return; // invalid squares

    auto &fromCell = grid[m.from.row][m.from.col];
    auto &toCell = grid[m.to.row][m.to.col];
    if (!fromCell)
        return; // nothing to move

    UndoInfo info;
    info.move = m;
    info.movedBefore = fromCell->getHasMoved(); // BEFORE moving it
    info.capturedPiece = std::move(toCell);     // take the captured piece out first

    toCell = std::move(fromCell); // move the piece
    toCell->setHasMoved(true);    // the piece is in toCell now

    // promotion: swap the pawn on 'to' for the chosen piece
    if (m.type == MoveType::PROMOTION)
    {
        info.promotedPawn = std::move(toCell); // keep the original pawn
        char letter = m.promotion;             // 'Q', 'R', 'B' or 'N'
        if (info.promotedPawn->getColour() == Colour::BLACK)
        {
            letter = static_cast<char>(std::tolower(static_cast<unsigned char>(letter)));
        }
        toCell = makePiece(letter); // new piece on 'to'
        toCell->setHasMoved(true);
    }
    // en_passant: remove the captured pawn from the board
    if (m.type == MoveType::EN_PASSANT)
    {
        info.capturedPiece = std::move(grid[m.from.row][m.to.col]);
    }
    // castling: the king already moved above, now move the rook too
    if (m.type == MoveType::CASTLE)
    {
        int row = m.to.row;
        int rookFrom = (m.to.col == 6) ? 7 : 0; // kingside: h-file, queenside: a-file
        int rookTo = (m.to.col == 6) ? 5 : 3;   // kingside: f-file, queenside: d-file
        grid[row][rookTo] = std::move(grid[row][rookFrom]);
        grid[row][rookTo]->setHasMoved(true);
    }
    history.push_back(std::move(info)); // save for undo
}

void Board::undoMove()
{
    if (history.empty())
        return; // nothing to undo

    UndoInfo info = std::move(history.back()); // take the last entry out
    history.pop_back();                        // then remove its empty slot

    auto &fromCell = grid[info.move.from.row][info.move.from.col];
    auto &toCell = grid[info.move.to.row][info.move.to.col];

    // promotion: put the original pawn back on 'to' (the queen gets deleted)
    if (info.move.type == MoveType::PROMOTION)
        toCell = std::move(info.promotedPawn);

    fromCell = std::move(toCell);            // 1. piece goes back to 'from'
    fromCell->setHasMoved(info.movedBefore); //    restore its old flag

    // 2. captured piece back where it was taken from
    if (info.move.type == MoveType::EN_PASSANT)
        grid[info.move.from.row][info.move.to.col] = std::move(info.capturedPiece);
    else
        toCell = std::move(info.capturedPiece);
    // castling: move the rook back to its corner
    if (info.move.type == MoveType::CASTLE)
    {
        int row = info.move.to.row;
        int rookFrom = (info.move.to.col == 6) ? 7 : 0;
        int rookTo = (info.move.to.col == 6) ? 5 : 3;
        grid[row][rookFrom] = std::move(grid[row][rookTo]);
        grid[row][rookFrom]->setHasMoved(false); // it had never moved, or castling wouldn't have been allowed
    }
}
std::vector<Move> Board::castlingMoves(Colour colour) const
{
    std::vector<Move> moves;
    int row = (colour == Colour::WHITE) ? 7 : 0;
    Colour enemy = (colour == Colour::WHITE) ? Colour::BLACK : Colour::WHITE;
    Position kingSq{row, 4};
    // small helpers, only used inside this function
    auto unmoved = [&](int col, char letter) { // own piece of this type, never moved?
        Piece *p = pieceAt(Position{row, col});
        return p && p->getColour() == colour && std::toupper(p->symbol()) == letter && !p->getHasMoved();
    };
    auto empty = [&](int col)
    { return pieceAt(Position{row, col}) == nullptr; };
    auto safe = [&](int col)
    { return !isAttacked(Position{row, col}, enemy); };

    // shared conditions: king on e-file, never moved, not in check right now
    if (!unmoved(4, 'K') || isInCheck(colour))
        return moves;
    // kingside: rook on h, f and g empty, f and g not attacked
    if (unmoved(7, 'R') && empty(5) && empty(6) && safe(5) && safe(6))
        moves.push_back(Move{kingSq, Position{row, 6}, MoveType::CASTLE});

    // queenside: rook on a, b c d empty, but only d and c must be safe
    if (unmoved(0, 'R') && empty(1) && empty(2) && empty(3) && safe(3) && safe(2))
        moves.push_back(Move{kingSq, Position{row, 2}, MoveType::CASTLE});

    return moves;
}
std::vector<Move> Board::legalMoves(Colour colour)
{
    std::vector<Move> result;
    for (int r = 0; r < 8; ++r)
    {
        for (int c = 0; c < 8; ++c)
        {
            Position from{r, c};
            Piece *p = pieceAt(from);
            if (p && p->getColour() == colour)
            {
                std::vector<Move> moves = p->candidateMoves(*this, from);
                for (const auto &m : moves)
                {
                    applyMove(m);
                    if (!isInCheck(colour))
                        result.push_back(m);
                    undoMove();
                }
            }
        }
    }
    std::vector<Move> castling = castlingMoves(colour);
    result.insert(result.end(), castling.begin(),
                  castling.end());
    return result;
}

bool Board::isCheckmate(Colour colour)
{
    return isInCheck(colour) && legalMoves(colour).empty();
}

bool Board::isStalemate(Colour colour)
{
    return !isInCheck(colour) && legalMoves(colour).empty();
}

const Move *Board::lastMove() const
{
    if (history.empty())
        return nullptr;
    return &history.back().move;
}

bool Board::isValidSetup() const
{
    int whiteKings = 0, blackKings = 0;
    for (int r = 0; r < 8; ++r)
    {
        for (int c = 0; c < 8; ++c)
        {
            Piece *p = pieceAt(Position{r, c});
            if (!p)
                continue;
            char t = static_cast<char>(std::toupper(static_cast<unsigned char>(p->symbol())));
            if (t == 'K')
            {
                if (p->getColour() == Colour::WHITE)
                    ++whiteKings;
                else
                    ++blackKings;
            }
            if (t == 'P' && (r == 0 || r == 7))
                return false; // pawn on the first or last row
        }
    }
    if (whiteKings != 1 || blackKings != 1)
        return false; // exactly one king each
    return !isInCheck(Colour::WHITE) && !isInCheck(Colour::BLACK);
}