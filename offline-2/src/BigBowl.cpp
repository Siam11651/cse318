#include "BigBowl.hpp"

BigBowl::BigBowl(const Player &player) : Bowl(player)
{
    count = 0;
}

size_t BigBowl::TakePebble(const Player &player, const size_t &hand)
{
    if(player == this->player)
    {
        ++count;

        return hand - 1;
    }
    else
    {
        return hand;
    }
}