#pragma once

#include "Player.hpp"
#include "Bowl.hpp"

class BigBowl : public Bowl
{
private:
    /* data */
public:
    BigBowl(const Player &player);
    size_t TakePebble(const Player &player, const size_t &hand);
    ~BigBowl();
};
