#include "Board.hpp"

bool Board::IsSolvableOddUtil() const
{
    if(GetInversionCount() % 2 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Board::IsSolvableEvenUtil() const
{
    size_t inversionCount = GetInversionCount();

    if((dimension - blankY) % 2 == 0 && inversionCount % 2 == 1)
    {
        return true;
    }
    else if((dimension - blankY) % 2 == 1 && inversionCount % 2 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

size_t Board::GetInversionCount() const
{
    size_t dimension1D = dimension * dimension - 1;
    uint64_t *array = new uint64_t[dimension1D];
    bool blankFound = false;

    for(size_t i = 0; i < dimension; ++i)
    {
        for(size_t j = 0; j < dimension; ++j)
        {
            if(boardArray[i][j] > 0)
            {
                if(blankFound)
                {
                    array[i * dimension + j - 1] = boardArray[i][j];
                }
                else
                {
                    array[i * dimension + j] = boardArray[i][j];
                }
            }
            else
            {
                blankFound = true;
            }
        }
    }

    size_t result = 0;

    for(size_t i = 0; i < dimension1D; ++i)
    {
        for(size_t j = i + 1; j < dimension1D; ++j)
        {
            if(array[i] > array[j])
            {
                ++result;
            }
        }
    }

    return result;
}

size_t Board::GetDepth() const
{
    return depth;
}

bool Board::CanShiftBoard(const Direction &direction) const
{
    if(direction == Direction::LEFT && blankX > 0)
    {
        return true;
    }
    else if(direction == Direction::RIGHT && blankX < dimension - 1)
    {
        return true;
    }
    else if(direction == Direction::UP && blankY > 0)
    {
        return true;
    }
    else if(direction == Direction::DOWN && blankY < dimension - 1)
    {
        return true;
    }

    return false;
}

std::vector<std::vector<uint64_t>> Board::GetShiftedBoardArray(const Direction &direction) const
{
    std::vector<std::vector<uint64_t>> newBoardArray = std::vector<std::vector<uint64_t>>(boardArray);

    for(size_t i = 0; i < dimension; ++i)
    {
        for(size_t j = 0; j < dimension; ++j)
        {
            newBoardArray[i][j] = GetCellValue(i, j);
        }
    }

    if(direction == Direction::LEFT)
    {
        std::swap(newBoardArray[GetBlankY()][GetBlankX()], newBoardArray[GetBlankY()][GetBlankX() - 1]);
    }
    else if(direction == Direction::RIGHT)
    {
        std::swap(newBoardArray[GetBlankY()][GetBlankX()], newBoardArray[GetBlankY()][GetBlankX() + 1]);
    }
    else if(direction == Direction::UP)
    {
        std::swap(newBoardArray[GetBlankY()][GetBlankX()], newBoardArray[GetBlankY() - 1][GetBlankX()]);
    }
    else if(direction == Direction::DOWN)
    {
        std::swap(newBoardArray[GetBlankY()][GetBlankX()], newBoardArray[GetBlankY() + 1][GetBlankX()]);
    }

    return newBoardArray;
}

Board::Board(const size_t &depth, const size_t &dimension, const std::vector<std::vector<uint64_t>> &boardArray, Board *parent)
{
    this->depth = depth;
    this->parent = parent;
    this->dimension = dimension;
    blankX = blankY = dimension;
    this->boardArray = std::vector<std::vector<uint64_t>>(boardArray);

    for(size_t i = 0; i < dimension; ++i)
    {
        for(size_t j = 0; j < dimension; ++j)
        {
            if(boardArray[i][j] == 0)
            {
                if(blankX == dimension)
                {
                    blankX = j;
                    blankY = i;
                }
                else
                {
                    // multiple blank exception
                }
            }
        }
    }
}

Board::Board(const Board &other)
{
    this->depth = other.depth;
    this->parent = other.parent;
    this->dimension = other.dimension;
    blankX = other.blankX;
    blankY = other.blankY;
    this->boardArray = std::vector<std::vector<uint64_t>>(other.boardArray);
}

size_t Board::GetBlankX() const
{
    return blankX;
}

size_t Board::GetBlankY() const
{
    return blankY;
}

size_t Board::GetDimension() const
{
    return dimension;
}

uint64_t Board::GetCellValue(const size_t &row, const size_t &column) const
{
    if(row >= dimension && column >= dimension)
    {
        // both beyond dimension exeption
    }
    else if(row >= dimension)
    {
        // both beyond dimension exeption
    }
    else if(column >= dimension)
    {
        // both beyond dimension exeption
    }
    else
    {
        return boardArray[row][column];
    }
}

Board *Board::GetParent() const
{
    return parent;
}

bool Board::IsSolvable() const
{
    if(dimension % 2 == 0)
    {
        return IsSolvableEvenUtil();
    }
    else
    {
        return IsSolvableOddUtil();
    }
}

bool Board::IsSolved() const
{
    bool solved = true;

    for(size_t i = 0; solved && i < dimension; ++i)
    {
        for(size_t j = 0; j < dimension; ++j)
        {
            uint64_t value = boardArray[i][j];

            if(value != 0 && i * dimension + j + 1 != value)
            {
                solved = false;

                break;
            }
        }
    }

    return solved;
}

bool Board::operator == (const Board &other)
{
    if(dimension == other.dimension)
    {
        for(size_t i = 0; i < dimension; ++i)
        {
            for(size_t j = 0; j < dimension; ++j)
            {
                if(boardArray[i][j] != other.boardArray[i][j])
                {
                    return false;
                }
            }
        }

        return true;
    }
    else
    {
        return false;
    }
}

Board::~Board()
{
    
}