#pragma once

#include <vector>
#include <set>
#include <cstdint>
#include <cstddef>

namespace offline_3
{
    class edge;

    class graph
    {
    private:
        size_t vertices_count;
        std::set<uint64_t> vertices_set;
        std::vector<int64_t> adjacency_matrix;
        std::vector<offline_3::edge> edge_list;

    public:
        graph(const uint64_t &vertices_count);
        void add_edge(const uint64_t &from, const uint64_t &to, const int64_t &weight);
        int64_t get_weight(const uint64_t &from, const uint64_t &to) const;
        offline_3::edge get_heaviest_edge() const;
        offline_3::edge get_lightest_edge() const;
        std::vector<offline_3::edge> get_restricted_candidate_edge_list(const int64_t &mu) const;
        const std::set<uint64_t> &get_vertices_id_set() const;
        uint64_t get_vertices_count() const;
        void clear();
    };
}