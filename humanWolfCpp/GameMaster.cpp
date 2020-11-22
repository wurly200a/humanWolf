#include <iostream>
#include "Player.hpp"
#include "GameMaster.hpp"

GameMaster::GameMaster()
{
    this->playerNum = (int)0;
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

        Player nowPlayer;

        nowPlayer.SetName(name);

        std::cout << "Your name is " + nowPlayer.GetName() + "\n";

        this->player[this->playerNum] = nowPlayer;
        this->playerNum++;
        if( this->playerNum < PLAYER_MAX )
        {
        }
        else
        {
            std::cout << "reached the maximum number.\n";
            break;
        }

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

    std::cout << "Players\n";
    for( int i=(int)0; i<this->playerNum; i++ )
    {
        std::cout << "  " + this->player[i].GetName() + "\n";
    }
}

void GameMaster::EndGame(void)
{
    std::cout << "<<<<<Game Over>>>>>\n";
}

void GameMaster::registerMember(void)
{
    std::cout << "<<<<<Game Over>>>>>\n";
}

int GameMaster::GetPlayerNum()
{
    return this->playerNum;
}
