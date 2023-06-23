#include "OutOfCellException.hpp"

OutOfCellException::OutOfCellException()
{

}

const char *OutOfCellException::what()
{
    std::string message = "Coordinate provided is out of board";

    return message.c_str();
}