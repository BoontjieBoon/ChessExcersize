#include "game.h"
#include "piece.h"
#include "enums.h"
#include "move.h"

Game::Game()
{
    playerOne.setSide(WHITE);
    playerTwo.setSide(BLACK);

    playerOne.setType(HUMAN);
    playerTwo.setType(COMPUTER);

    activePlayer = &playerOne;
}

Game::~Game()
{

}

Player *Game::changeActivePlayer()
{
    if (activePlayer == &playerOne)
    {
        activePlayer = &playerTwo;
    }
    else
    {
        activePlayer = &playerOne;
    }

    return activePlayer;
}

Player *Game::getActivePlayer()
{
    return this->activePlayer;
}
