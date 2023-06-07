#pragma once

#include "Board.hpp"

class BoardComparator
{
public:
    bool operator ()(Board *left, Board *right);
};