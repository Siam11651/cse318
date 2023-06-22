#include "ManhattanBoard.hpp"

ManhattanBoard::ManhattanBoard(const size_t &depth, const size_t &dimension, const std::vector<uint64_t> &boardArray, Board *parent) : Board(depth, dimension, boardArray, parent)
{
    
}

uint64_t ManhattanBoard::GetPriority() const
{
    size_t depth = GetDepth();
    uint64_t result = 0;
    size_t dimension = GetDimension();

    for(size_t i = 0; i < dimension; ++i)
    {
        for(size_t j = 0; j < dimension; ++j)
        {
            uint64_t value = GetCellValue(i, j);

            if(value != 0)
            {
                size_t targetRow = (value - 1) / dimension;
                size_t targetColumn = (value - 1) % dimension;

                uint64_t gap = 0;

                if(targetRow > i)
                {
                    gap += targetRow - i;
                }
                else
                {
                    gap += i - targetRow;
                }

                if(targetColumn > j)
                {
                    gap += targetColumn - j;
                }
                else
                {
                    gap += j - targetColumn;
                }

                result += gap;
            }
        }
    }

    return result + depth;
}

Board *ManhattanBoard::CreateNewChildBoard(const Direction &direction) const
{
    if(!CanShiftBoard(direction))
    {
        return nullptr;
    }

    return new ManhattanBoard(GetDepth() + 1, GetDimension(), GetShiftedBoardArray(direction), (Board *)this);
}