#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "player.h"
#include "enums.h"

class PlayerController
{
private:
    Player* activePlayer;
    Player white;
    Player black;
public:
    PlayerController();
    PlayerController(PlayerType whiteType, PlayerType blackType);
    ~PlayerController();
    void reset(PlayerType whiteType, PlayerType blackType);
    Player *changeActivePlayer();
    Player *getActivePlayer();
};

#endif // PLAYERCONTROLLER_H
