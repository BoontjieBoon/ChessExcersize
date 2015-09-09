#include "piece.h"

Piece::Piece(Side side, PieceType type)
{
    this->setSide(side);
    this->setType(type);
}

Piece::~Piece()
{
}

Side Piece::getSide()
{
    return this->_side;
}

void Piece::setSide(Side side)
{
    this->_side = side;
}

PieceType Piece::getType()
{
    return this->_type;
}

void Piece::setType(PieceType type)
{
    this->_type = type;
}
