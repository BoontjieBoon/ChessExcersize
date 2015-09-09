#ifndef PLAYER_H
#define PLAYER_H

#include <enums.h>

class Player
{
private:
    Side _side;
    PlayerType _type;
public:
    Player();
    Player(Side side, PlayerType type);

    void setSide(Side side);
    Side getSide();

    void setType(PlayerType type);
    PlayerType getType();
};

#endif // PLAYER_H
