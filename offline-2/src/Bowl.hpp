#pragma once

#include "Player.hpp"

class Bowl
{
protected:
    Player player;
    size_t count;

public:
    Bowl(const Player &player);
    virtual size_t TakePebble(const Player &player, const size_t &hand);
    ~Bowl();
};