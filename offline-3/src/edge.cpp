#include "edge.hpp"

offline_3::edge::edge(const offline_3::vertex &from, const offline_3::vertex &to, const int64_t &weight)
{
    this->from = from;
    this->to = to;
    this->weight = weight;
}

offline_3::vertex offline_3::edge::get_from() const
{
    return from;
}

offline_3::vertex offline_3::edge::get_to() const
{
    return to;
}

int64_t offline_3::edge::get_weight() const
{
    return weight;
}