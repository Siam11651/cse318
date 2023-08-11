#pragma once

#include <memory>
#include "graph.hpp"

namespace offline_3
{
    class maxcut_solver
    {
    public:
        static std::pair<std::pair<std::shared_ptr<std::set<offline_3::vertex>>, std::shared_ptr<std::set<offline_3::vertex>>>, int64_t> get_maxcut(const offline_3::graph &graph);
        static std::pair<std::shared_ptr<std::set<offline_3::vertex>>, std::shared_ptr<std::set<offline_3::vertex>>> get_semi_greedy_maxcut(const offline_3::graph &graph);
        static std::pair<std::shared_ptr<std::set<offline_3::vertex>>, std::shared_ptr<std::set<offline_3::vertex>>> get_local_search_maxcut(const offline_3::graph &graph);
        static int64_t get_cut_weight(const std::set<offline_3::vertex> &vertices_set1, const std::set<offline_3::vertex> &vertices_set2);
    };
}