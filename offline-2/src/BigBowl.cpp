#include "BigBowl.hpp"

BigBowl::BigBowl(const Player &player) : Bowl(player)
{
    count = 0;
}

BigBowl::BigBowl(const Bowl &other) : Bowl(other)
{
    
}

bool BigBowl::TakePebble(const Player &player, size_t &hand)
{
    if(player == this->player)
    {
        ++count;
        --hand;

        return true;
    }
    else
    {
        return false;;
    }
}

BigBowl::~BigBowl()
{
    
}