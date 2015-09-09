#include "player.h"

Player::Player()
{
    this->setSide(WHITE);
    this->setType(COMPUTER);
}

Player::Player(Side side, PlayerType type)
{
    this->setSide(side);
    this->setType(type);
}

void Player::setSide(Side side)
{
    this->_side = side;
}

Side Player::getSide()
{
    return this->_side;
}

void Player::setType(PlayerType type)
{
    this->_type = type;
}

PlayerType Player::getType()
{
    return this->_type;
}
