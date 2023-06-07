#include "HammingBoard.hpp"

HammingBoard::HammingBoard(const size_t &depth, const size_t &dimension, const std::vector<std::vector<uint64_t>> &boardArray, Board *parent) : Board(depth, dimension, boardArray, parent)
{
    
}

uint64_t HammingBoard::GetPriority() const
{
    size_t depth = GetDepth();
    size_t dimension = GetDimension();
    uint64_t count = 0;

    for(size_t i = 0; i < dimension; ++i)
    {
        for(size_t j = 0; j < dimension; ++j)
        {
            uint64_t value = GetCellValue(i, j);

            if(value > 0 && value != (i * dimension + j + 1))
            {
                ++count;
            }
        }
    }

    return count + depth;
}

Board *HammingBoard::CreateNewChildBoard(const Direction &direction) const
{
    if(!CanShiftBoard(direction))
    {
        return nullptr;
    }

    return new HammingBoard(GetDepth() + 1, GetDimension(), GetShiftedBoardArray(direction), (Board *)this);
}