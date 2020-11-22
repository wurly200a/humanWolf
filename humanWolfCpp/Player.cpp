#include <iostream>
#include "Player.hpp"

Player::Player()
{
    this->playerName = playerName;
}

Player::~Player()
{
}

void Player::SetName(std::string playerName)
{
    this->playerName = playerName;
}

std::string Player::GetName(void)
{
    return this->playerName;
}
