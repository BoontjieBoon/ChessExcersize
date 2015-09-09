#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "enums.h"

class Game
{
private:
    GameState state;
    Player* activePlayer;
    Player white;
    Player black;
public:
    Game();
    Game(PlayerType whiteType, PlayerType blackType);
    ~Game();
    void reset(PlayerType whiteType, PlayerType blackType);
    Player *changeActivePlayer();
    Player *getActivePlayer();
};

#endif // GAME_H
