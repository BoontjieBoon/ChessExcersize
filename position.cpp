#include <position.h>
#include <cmath>
#include <algorithm>

Position::Position()
{
    this->setFile(-1);
    this->setRank(-1);
}

Position::Position(int file, int rank)
{
    this->setFile(file);
    this->setRank(rank);
}

Position::~Position()
{
}

int Position::getFile() const
{
    return _file;
}

void Position::setFile(int file)
{
    this->_file = file;
}

int Position::getRank() const
{
    return _rank;
}

void Position::setRank(int rank)
{
    this->_rank = rank;
}

int Position::getDistance(const Position &p)
{
    return std::max(std::abs(this->getFile()-p.getFile()), std::abs(this->getRank()-p.getRank()));
}

Position Position::operator +(const Position& p)
{
    return Position(this->getFile() + p.getFile(), this->getRank() + p.getRank());
}

Position& Position::operator +=(const Position& p)
{
    this->setFile(this->getFile() + p.getFile());
    this->setRank(this->getRank() + p.getRank());
    return *this;
}

bool Position::operator ==(const Position& p)
{
    return ((this->getFile() == p.getFile()) && (this->getRank() == p.getRank()));
}
