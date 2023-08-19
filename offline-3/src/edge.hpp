#pragma once

#include <cstdint>

namespace offline_3
{
    class edge
    {
    private:
        uint64_t from;
        uint64_t to;
        int64_t weight;

    public:
        edge(const uint64_t &from, const uint64_t &to, const int64_t &weight);
        uint64_t get_from() const;
        uint64_t get_to() const;
        int64_t get_weight() const;
        bool operator < (const offline_3::edge &other) const;
        bool operator > (const offline_3::edge &other) const;
    };
}