#include <iostream>
#include "GameMaster.hpp"

GameMaster::GameMaster()
{
}

GameMaster::~GameMaster()
{
}

void GameMaster::StartGame(void)
{
    std::cout << "Game Start.\n";
}

void GameMaster::EndGame(void)
{
    std::cout << "Game Over.\n";
}
