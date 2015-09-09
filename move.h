#ifndef MOVE_H
#define MOVE_H

#include "position.h"

class Move
{
private:
    Position _start;
    Position _stop;
public:
    Move();
    Move(Position start, Position offset);

    Position getStart();
    void setStart(Position position);

    Position getStop();
    void setStop(Position position);

    Move& operator += (const Position& p);
};

#endif // MOVE_H
