#include "BoardComparator.hpp"

bool BoardComparator::operator () (Board *left, Board *right)
{
    uint64_t leftPriority = left->GetPriority();
    uint64_t rightPriority = right->GetPriority();

    return left->GetPriority() > right->GetPriority();
}