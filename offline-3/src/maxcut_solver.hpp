#pragma once

#include <random>
#include <memory>
#include "graph.hpp"

namespace offline_3
{
    typedef std::pair<std::set<uint64_t>, std::set<uint64_t>> maxcut;

    class maxcut_solver
    {
    private:
        static uint64_t iteration_count;
        static bool is_semi_greedy;
        static offline_3::maxcut get_greedy_maxcut(const offline_3::graph &graph);
        static void local_search_optimization(const offline_3::graph &graph, std::set<uint64_t> &vertices_set1, std::set<uint64_t> &vertices_set2);
        static std::mt19937_64 prng_engine;    // mersenne twister pseudo random number generator engine

    public:
        static offline_3::maxcut get_maxcut(const offline_3::graph &graph);
        static int64_t get_cut_weight(const offline_3::graph &graph, const std::set<uint64_t> &vertices_set1, const std::set<uint64_t> &vertices_set2);
        static void set_iteration_count(const uint64_t &iteration_count);
        static void set_semi_greedy(const bool &is_semi_greedy);
    };
}