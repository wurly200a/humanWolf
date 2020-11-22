#pragma once

#include <string>
#include "Player.hpp"

#define PLAYER_MAX 10

class GameMaster
{
private:
    int playerNum;
    Player player[PLAYER_MAX];
    void registerMember();
public:
    GameMaster(); // counstructor
    ~GameMaster(); // decounstructor
    void PrepareGame(void);
    void StartGame(void);
    void EndGame(void);
    int GetPlayerNum(void);
};
