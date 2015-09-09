#ifndef PIECE_H
#define PIECE_H

#include <QVector>
#include <enums.h>

using namespace std;

class Piece
{
private:
    Side _side;
    PieceType _type;
public:
    Piece(Side side, PieceType type);
    ~Piece();

    Side getSide();
    void setSide(Side side);
    PieceType getType();
    void setType(PieceType type);
};

#endif // PIECE_H
