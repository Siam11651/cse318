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

Board::Board(const size_t &depth, const size_t &dimension, uint64_t **boardArray, Board *parent)
{
    this->depth = depth;
    this->parent = parent;
    this->dimension = dimension;
    blankX = blankY = dimension;
    this->boardArray = new uint64_t *[dimension];

    for(size_t i = 0; i < dimension; ++i)
    {
        this->boardArray[i] = new uint64_t[dimension];

        for(size_t j = 0; j < dimension; ++j)
        {
            this->boardArray[i][j] = boardArray[i][j];

            if(boardArray[i][j] == 0)
            {
                if(blankX == dimension)
                {
                    blankX = j;
                    blankY = i;
                }
                else
                {
                    // more than one 0 exception
                }
            }
        }
    }
}

bool Board::ShiftBoard(const Direction &direction)
{
    if(direction == Direction::LEFT)
    {
        if(blankX > 0)
        {
            std::swap(boardArray[blankY][blankX], boardArray[blankY][blankX - 1]);

            --blankX;
        }
        else
        {
            return false;
        }
    }
    else if(direction == Direction::RIGHT)
    {
        if(blankX < dimension - 1)
        {
            std::swap(boardArray[blankY][blankX], boardArray[blankY][blankX + 1]);

            ++blankX;
        }
        else
        {
            return false;
        }
    }
    else if(direction == Direction::UP)
    {
        if(blankY > 0)
        {
            std::swap(boardArray[blankY][blankX], boardArray[blankY - 1][blankX]);

            --blankY;
        }
        else
        {
            return false;
        }
    }
    else if(direction == Direction::DOWN)
    {
        if(blankY < dimension - 1)
        {
            std::swap(boardArray[blankY][blankX], boardArray[blankY][blankX + 1]);

            ++blankX;
        }
        else
        {
            return false;
        }
    }

    return true;
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

Board::~Board()
{
    for(size_t i = 0; i < dimension; ++i)
    {
        delete boardArray[i];
    }

    delete boardArray;
}