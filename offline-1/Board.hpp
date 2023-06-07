#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <vector>
#include "Direction.hpp"

class Board
{
private:
    size_t dimension, blankX, blankY, depth;
    std::vector<std::vector<uint64_t>> boardArray;
    Board *parent;

    bool IsSolvableOddUtil() const;
    bool IsSolvableEvenUtil() const;
    size_t GetInversionCount() const;

protected:
    size_t GetDepth() const;
    bool CanShiftBoard(const Direction &direction) const;
    std::vector<std::vector<uint64_t>> GetShiftedBoardArray(const Direction &direction) const;

public:
    Board(const size_t &depth, const size_t &dimension, const std::vector<std::vector<uint64_t>> &boardArray, Board *parent);
    Board(const Board &other);
    virtual uint64_t GetPriority() const = 0;
    virtual Board *CreateNewChildBoard(const Direction &direction) const = 0;
    size_t GetBlankX() const;
    size_t GetBlankY() const;
    size_t GetDimension() const;
    uint64_t GetCellValue(const size_t &row, const size_t &column) const;
    Board *GetParent() const;
    bool IsSolvable() const;
    bool IsSolved() const;
    bool operator == (const Board &other);
    ~Board();
};