#include "move.h"

Move::Move()
{
}

Move::Move(Position start, Position offset)
{
    this->setStart(start);
    this->setStop(start + offset);
}

Position Move::getStart()
{
    return this->_start;
}

void Move::setStart(Position position)
{
    this->_start = position;
}

Position Move::getStop()
{
    return this->_stop;
}

void Move::setStop(Position position)
{
    this->_stop = position;
}

Move& Move::operator += (const Position& p)
{
    this->setStop(this->getStop() + p);
    return *this;
}
