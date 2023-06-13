#pragma once

#include <ostream>
#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <vector>
#include "Direction.hpp"
#include "OutOfCellException.hpp"

class Board
{
private:
    size_t dimension, blankX, blankY, depth;
    std::vector<uint64_t> boardArray;
    Board *parent;

    bool IsSolvableOddUtil() const;
    bool IsSolvableEvenUtil() const;
    size_t GetInversionCount() const;

protected:
    bool CanShiftBoard(const Direction &direction) const;
    std::vector<uint64_t> GetShiftedBoardArray(const Direction &direction) const;

public:
    Board(const size_t &depth, const size_t &dimension, const std::vector<uint64_t> &boardArray, Board *parent);
    Board(const Board &other);
    size_t GetDepth() const;
    virtual uint64_t GetPriority() const;
    virtual Board *CreateNewChildBoard(const Direction &direction) const;
    size_t GetBlankX() const;
    size_t GetBlankY() const;
    size_t GetDimension() const;
    uint64_t GetCellValue(const size_t &row, const size_t &column) const;
    Board *GetParent() const;
    bool IsSolvable() const;
    bool IsSolved() const;
    void Print(std::ostream &outputStream) const;
    bool operator == (const Board &other) const;
    bool operator < (const Board &other) const;
    bool operator > (const Board &other) const;
    bool operator <= (const Board &other) const;
    bool operator >= (const Board &other) const;
    ~Board();
};