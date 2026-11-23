#include "colourDisplay.h"
#include <cctype>
#include "board.h"

namespace
{
    const char *RESET = "\033[0m";
    const char *LIGHT_SQ = "\033[48;5;223m"; // cream
    const char *DARK_SQ = "\033[48;5;179m";  // tan
    const char *PIECE = "\033[30m";          // black ink for every piece

    // outlined symbols for white, filled for black
    const char *glyph(char letter, bool white)
    {
        switch (letter)
        {
        case 'K':
            return white ? "♔" : "♚";
        case 'Q':
            return white ? "♕" : "♛";
        case 'R':
            return white ? "♖" : "♜";
        case 'B':
            return white ? "♗" : "♝";
        case 'N':
            return white ? "♘" : "♞";
        default:
            return white ? "♙" : "♟";
        }
    }
}

void ColourDisplay::notify(const Board &b)
{
    for (int r = 0; r < 8; ++r)
    {
        out << " " << 8 - r << " ";
        for (int c = 0; c < 8; ++c)
        {
            out << (((r + c) % 2 == 0) ? LIGHT_SQ : DARK_SQ);
            Piece *p = b.pieceAt(Position{r, c});
            if (!p)
            {
                out << "   ";
            }
            else
            {
                char letter = static_cast<char>(std::toupper(static_cast<unsigned char>(p->symbol())));
                bool white = (p->getColour() == Colour::WHITE);
                out << PIECE << " " << glyph(letter, white) << " ";
            }
            out << RESET;
        }
        out << "\n";
    }
    out << "\n    a  b  c  d  e  f  g  h\n";
}