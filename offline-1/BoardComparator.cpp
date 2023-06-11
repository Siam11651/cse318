#include "BoardComparator.hpp"

bool BoardComparator::operator () (Board *left, Board *right)
{
    return left->GetPriority() > right->GetPriority();
}