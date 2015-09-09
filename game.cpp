#include "game.h"
#include "piece.h"
#include "enums.h"
#include "move.h"

Game::Game()
    :Game(HUMAN, COMPUTER)
{
}

Game::Game(PlayerType whiteType, PlayerType blackType)
{
    white.setSide(WHITE);
    black.setSide(BLACK);

    white.setType(whiteType);
    white.setType(blackType);

    activePlayer = &white;
}

Game::~Game()
{

}

void Game::reset(PlayerType whiteType, PlayerType blackType)
{
    white.setType(whiteType);
    black.setType(blackType);

    activePlayer = &white;
}

Player *Game::changeActivePlayer()
{
    if (activePlayer == &white)
    {
        activePlayer = &black;
    }
    else
    {
        activePlayer = &white;
    }

    return activePlayer;
}

Player *Game::getActivePlayer()
{
    return this->activePlayer;
}
