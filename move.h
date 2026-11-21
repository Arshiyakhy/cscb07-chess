#ifndef MOVE_H
#define MOVE_H
#include "position.h"

enum class MoveType{
    NORMAL,
    DOUBLE_PAWN,
    CASTLE,
    EN_PASSANT,
    PROMOTION
};

struct Move{
Position from;
Position to;
MoveType type=MoveType::NORMAL;
char promotion = ' ';
bool operator==(const Move &other) const;
};

#endif