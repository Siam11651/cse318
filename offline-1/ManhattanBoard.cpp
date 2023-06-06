#include "ManhattanBoard.hpp"

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

            if(value > 0)
            {
                size_t targetRow = value / dimension;
                size_t targetColumn = value % dimension;
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