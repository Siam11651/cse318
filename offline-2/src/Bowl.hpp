#pragma once

#include <cstddef>
#include "Player.hpp"

class Bowl
{
protected:
    Player player;
    size_t count;

public:
    Bowl(const Player &player);
    Bowl(const Bowl &other);
    size_t GetCount() const;
    void SetCount(const size_t &count);
    virtual bool TakePebble(const Player &player, size_t &hand);
    ~Bowl();
};