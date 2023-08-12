#pragma once

#include <cstdint>
#include <vector>
#include <map>
#include <memory>

namespace offline_3
{
    class edge;

    class vertex
    {
    private:
        uint64_t id;
        std::map<uint64_t, int64_t> *adjacents;

    public:
        vertex(const uint64_t &id = 0);
        uint64_t get_id() const;
        void insert_adjacent(const uint64_t &id, const int64_t &weight) const;
        int64_t get_weight(const uint64_t &id) const;
        offline_3::edge get_heaviest_adjacent() const;
        offline_3::edge get_lightest_adjacent() const;
        bool has_adjacent(const uint64_t &id) const;
        std::vector<offline_3::edge> get_restricted_adjacent_list(const int64_t &mu) const;
        bool operator < (const offline_3::vertex &other) const;
    };
}