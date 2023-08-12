#pragma once

#include <memory>
#include "graph.hpp"

namespace offline_3
{
    typedef std::pair<std::set<uint64_t>, std::set<uint64_t>> maxcut;

    class maxcut_solver
    {
    private:
        static offline_3::maxcut get_semi_greedy_maxcut(const offline_3::graph &graph);
        static void local_search_optimization(const offline_3::graph &graph, std::set<uint64_t> &vertices_set1, std::set<uint64_t> &vertices_set2);

    public:
        static offline_3::maxcut get_maxcut(const offline_3::graph &graph);
        static int64_t get_cut_weight(const offline_3::graph &graph, const std::set<uint64_t> &vertices_set1, const std::set<uint64_t> &vertices_set2);
    };
}