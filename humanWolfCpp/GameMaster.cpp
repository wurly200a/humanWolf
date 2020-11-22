#include <iostream>
#include "GameMaster.hpp"

GameMaster::GameMaster()
{
}

GameMaster::~GameMaster()
{
}

void GameMaster::PrepareGame(void)
{
    std::string name;
    char c;

    std::cout << "<<<<<Prepere Game >>>>>\n";
    do
    {
        std::cout << "Input name.\n";
        std::cin >> name;
        std::cout << "Your name is " + name + ".\n";
        std::cout << "Is there next person?(y/n)\n";
        do
        {
            std::cin >> c;
        } while ( !(c=='y' || c=='n') );

    } while ( c!='n' );
}

void GameMaster::StartGame(void)
{
    std::cout << "<<<<<Game Start>>>>>\n";
}

void GameMaster::EndGame(void)
{
    std::cout << "<<<<<Game Over>>>>>\n";
}

void GameMaster::registerMember(void)
{
    std::cout << "<<<<<Game Over>>>>>\n";
}
