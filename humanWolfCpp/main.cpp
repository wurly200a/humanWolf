#include <iostream>
#include <string>
#include "GameMaster.hpp"
int
humanWolfMain(int argc, char* argv[])
{
    char c;
    GameMaster gameMaster;

    gameMaster.PrepareGame();
    do
    {
        gameMaster.StartGame();
        gameMaster.EndGame();

        do
        {
            std::cout << "Continue?(y/n)\n";
            std::cin >> c;
        } while ( !(c=='y' || c=='n') );
    } while ( c!='n' );

    return 0;
}
