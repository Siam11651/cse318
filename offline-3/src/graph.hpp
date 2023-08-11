#pragma once

#include <vector>
#include <set>
#include <cstdint>
#include "edge.hpp"

namespace offline_3
{
    class vertex;

    class graph
    {
    private:
        std::set<offline_3::vertex> vertices;

    public:
        graph(const uint64_t &initial_size = 0);
        bool add_vertex(const uint64_t &id);
        bool add_edge(const uint64_t &from, const uint64_t &to, const int64_t &weight);
        offline_3::vertex get_vertex(const uint64_t &index) const;
        offline_3::edge get_heaviest_edge() const;
        offline_3::edge get_lightest_edge() const;
        std::shared_ptr<std::vector<offline_3::edge>> get_restricted_candidate_list(const int64_t &mu) const;
        void clear();
    };
}