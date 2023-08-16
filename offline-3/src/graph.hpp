#pragma once

#include <vector>
#include <set>
#include <cstdint>

namespace offline_3
{
    class edge;
    class vertex;

    class graph
    {
    private:
        std::vector<offline_3::vertex> vertices;

    public:
        graph(const uint64_t &initial_size = 0);
        bool add_edge(const uint64_t &from, const uint64_t &to, const int64_t &weight);
        const offline_3::vertex &get_vertex(const uint64_t &index) const;
        offline_3::edge get_heaviest_edge() const;
        offline_3::edge get_lightest_edge() const;
        std::vector<offline_3::edge> get_restricted_candidate_edge_list(const int64_t &mu) const;
        std::set<uint64_t> get_vertices_id_set() const;
        uint64_t get_vertices_count() const;
        void clear();
    };
}