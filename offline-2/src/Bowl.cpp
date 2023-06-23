#include "Bowl.hpp"

Bowl::Bowl(const Player &player)
{
    this->player = player;
    count = 4;
}

size_t Bowl::TakePebble(const Player &player, const size_t &hand)
{
    ++count;

    return hand - 1;
}