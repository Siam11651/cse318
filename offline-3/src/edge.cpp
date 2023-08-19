#include "edge.hpp"

offline_3::edge::edge(const uint64_t &from, const uint64_t &to, const int64_t &weight)
{
    this->from = from;
    this->to = to;
    this->weight = weight;
}

uint64_t offline_3::edge::get_from() const
{
    return from;
}

uint64_t offline_3::edge::get_to() const
{
    return to;
}

int64_t offline_3::edge::get_weight() const
{
    return weight;
}

bool offline_3::edge::operator < (const offline_3::edge &other) const
{
    return weight < other.weight;
}

bool offline_3::edge::operator > (const offline_3::edge &other) const
{
    return weight > other.weight;
}