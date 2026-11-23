#include "humanPlayer.h"
#include <string>
#include <cctype>

Move HumanPlayer::getMove(Board &, Colour, std::istream &args)
{
    std::string fromStr, toStr, promoStr;
    if (!(args >> fromStr >> toStr))
        return Move{};                          // missing squares, e.g. just "move e2"

    Position from = Position::fromString(fromStr);
    Position to = Position::fromString(toStr);
    if (!from.inBounds() || !to.inBounds())
        return Move{};                          // bad squares, e.g. "move z9 e4"

    char promo = ' ';
    if (args >> promoStr && !promoStr.empty()) // optional promotion letter
        promo = static_cast<char>(std::toupper(static_cast<unsigned char>(promoStr[0])));

    return Move{from, to, MoveType::NORMAL, promo};
}