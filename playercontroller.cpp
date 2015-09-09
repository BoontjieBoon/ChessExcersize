#include "playercontroller.h"
#include "piece.h"
#include "enums.h"
#include "move.h"

PlayerController::PlayerController()
    :PlayerController(HUMAN, COMPUTER)
{
}

PlayerController::PlayerController(PlayerType whiteType, PlayerType blackType)
{
    white.setSide(WHITE);
    black.setSide(BLACK);

    white.setType(whiteType);
    white.setType(blackType);

    activePlayer = &white;
}

PlayerController::~PlayerController()
{

}

void PlayerController::reset(PlayerType whiteType, PlayerType blackType)
{
    white.setType(whiteType);
    black.setType(blackType);

    activePlayer = &white;
}

Player *PlayerController::changeActivePlayer()
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

Player *PlayerController::getActivePlayer()
{
    return this->activePlayer;
}
