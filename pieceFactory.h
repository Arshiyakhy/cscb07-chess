#ifndef PIECEFACTORY_H
#define PIECEFACTORY_H
#include <memory>
#include "piece.h"

std::unique_ptr<Piece> makePiece(char letter);

#endif