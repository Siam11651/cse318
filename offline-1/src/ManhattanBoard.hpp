#pragma once

#include "Board.hpp"

class ManhattanBoard : public Board
{
public:
    ManhattanBoard(const size_t &depth, const size_t &dimension, const std::vector<uint64_t> &boardArray, Board *parent);
    uint64_t GetPriority() const;
    Board *CreateNewChildBoard(const Direction &direction) const;
};