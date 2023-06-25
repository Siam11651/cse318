#pragma once

#include "Player.hpp"
#include "Bowl.hpp"

class BigBowl : public Bowl
{
private:
    /* data */
public:
    BigBowl(const Player &player);
    BigBowl(const Bowl &other);
    bool TakePebble(const Player &player, size_t &hand);
    ~BigBowl();
};
