#pragma once

#include <exception>
#include <string>

class OutOfCellException : public std::exception
{
public:
    OutOfCellException();
    const char *what();
};