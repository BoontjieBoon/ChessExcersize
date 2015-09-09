#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "enums.h"

class Game
{
private:
    GameState state;
    Player* activePlayer;
    Player playerOne;
    Player playerTwo;
public:
    Game();
    ~Game();
    Player *changeActivePlayer();
    Player *getActivePlayer();
};

#endif // GAME_H
