#include "textDisplay.h"
#include "board.h"

void TextDisplay::notify(const Board &b)
{
    out << b; // the exact spec format, from Board's operator<<
}