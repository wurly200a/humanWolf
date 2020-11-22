#pragma once

#include <string>

class Player
{
private:
    std::string playerName;
public:
    Player(); // counstructor
    ~Player(); // decounstructor
    void SetName(std::string playerName);
    std::string GetName(void);
};
