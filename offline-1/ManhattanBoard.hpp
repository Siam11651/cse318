#pragma once

#include "Board.hpp"

class ManhattanBoard : public Board
{
public:
    uint64_t GetPriority() const;
};