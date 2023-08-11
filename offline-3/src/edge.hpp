#pragma once

#include "vertex.hpp"

namespace offline_3
{
    class edge
    {
    private:
        offline_3::vertex from;
        offline_3::vertex to;
        int64_t weight;

    public:
        edge(const offline_3::vertex &from, const offline_3::vertex &to, const int64_t &weight);
        offline_3::vertex get_from() const;
        offline_3::vertex get_to() const;
        int64_t get_weight() const;
    };
}