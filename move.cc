#include "move.h"

bool Move::operator==(const Move &other) const{
    return other.to==to && other.from==from && other.promotion ==promotion;
}