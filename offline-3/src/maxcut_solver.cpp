#include <random>
#include "maxcut_solver.hpp"
#include "vertex.hpp"
#include "edge.hpp"

std::pair<std::pair<std::shared_ptr<std::set<offline_3::vertex>>, std::shared_ptr<std::set<offline_3::vertex>>>, int64_t> offline_3::maxcut_solver::get_maxcut(const offline_3::graph &graph)
{
    int64_t max_weight = INT64_MIN;

    while(true)
    {

    }

    return {{nullptr, nullptr}, 0};
}

std::pair<std::shared_ptr<std::set<offline_3::vertex>>, std::shared_ptr<std::set<offline_3::vertex>>> offline_3::maxcut_solver::get_semi_greedy_maxcut(const offline_3::graph &graph)
{
    std::mt19937_64 prng_engine;
    double_t alpha = (double_t)prng_engine() / std::mt19937_64::max();
    offline_3::edge lightest_edge = graph.get_lightest_edge();
    offline_3::edge heaviest_edge = graph.get_heaviest_edge();
    double_t mu = lightest_edge.get_weight() + alpha * (heaviest_edge.get_weight() - lightest_edge.get_weight());
    std::shared_ptr<std::vector<offline_3::edge>> rcl = graph.get_restricted_candidate_list(mu);

    return {nullptr, nullptr};
}

std::pair<std::shared_ptr<std::set<offline_3::vertex>>, std::shared_ptr<std::set<offline_3::vertex>>> offline_3::maxcut_solver::get_local_search_maxcut(const offline_3::graph &graph)
{
    return {nullptr, nullptr};
}

int64_t offline_3::maxcut_solver::get_cut_weight(const std::set<offline_3::vertex> &vertices_set1, const std::set<offline_3::vertex> &vertices_set2)
{
    int64_t weight = 0;

    for(std::set<offline_3::vertex>::iterator iterator1 = vertices_set1.begin(); iterator1 != vertices_set1.end(); ++iterator1)
    {
        for(std::set<offline_3::vertex>::iterator iterator2 = vertices_set2.begin(); iterator2 != vertices_set2.end(); ++iterator2)
        {
            weight += iterator1->get_weight(iterator2->get_id());
        }
    }

    return weight;
}