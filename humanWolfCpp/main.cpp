#include <iostream>
#include "GameMaster.hpp"

int
humanWolfMain(int argc, char* argv[])
{
    GameMaster gameMaster;

    gameMaster.StartGame();
    gameMaster.EndGame();

    return 0;
}
