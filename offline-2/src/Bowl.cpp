#include "Bowl.hpp"

Bowl::Bowl(const Player &player)
{
    this->player = player;
    count = 4;
}

Bowl::Bowl(const Bowl &other)
{
    player = other.player;
    count = other.count;
}

size_t Bowl::GetCount() const
{
    return count;
}

void Bowl::SetCount(const size_t &count)
{
    this->count = count;
}

bool Bowl::TakePebble(const Player &player, size_t &hand)
{
    ++count;
    --hand;

    return false;
}