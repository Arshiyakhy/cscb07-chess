#include "pieceFactory.h"
#include <cctype>
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "pawn.h"

std::unique_ptr<Piece> makePiece(char letter){
    unsigned char c = static_cast<unsigned char>(letter);
    Colour colour = std::isupper(c) ? Colour::WHITE : Colour::BLACK;

    switch(std::toupper(c)){
        case 'K' : return std::make_unique<king>(colour);
        case 'Q' : return std::make_unique<Queen>(colour);
        case 'R' : return std::make_unique<Rook>(colour);
        case 'B' : return std::make_unique<Bishop>(colour);
        case 'N' : return std::make_unique<Knight>(colour);
        case 'P' : return std::make_unique<Pawn>(colour);
        default: return nullptr;
    }
}