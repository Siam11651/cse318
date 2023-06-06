#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include "Direction.hpp"

class Board
{
private:
    size_t dimension, blankX, blankY, depth;
    uint64_t **boardArray;
    Board *parent;

    bool IsSolvableOddUtil() const;
    bool IsSolvableEvenUtil() const;
    size_t GetInversionCount() const;

protected:
    size_t GetDepth() const;

public:
    Board(const size_t &depth, const size_t &dimension, uint64_t **boardArray, Board *parent);
    bool ShiftBoard(const Direction &direction);
    virtual uint64_t GetPriority() const = 0;
    size_t GetBlankX() const;
    size_t GetBlankY() const;
    size_t GetDimension() const;
    uint64_t GetCellValue(const size_t &row, const size_t &column) const;
    bool IsSolvable() const;
    ~Board();
};