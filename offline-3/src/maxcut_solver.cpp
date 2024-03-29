#include <iostream>
#include <algorithm>
#include "maxcut_solver.hpp"
#include "edge.hpp"

uint64_t offline_3::maxcut_solver::iteration_count = 50;
uint16_t offline_3::maxcut_solver::greedy_level = 2;
std::mt19937_64 offline_3::maxcut_solver::prng_engine;

std::tuple<int64_t, int64_t, uint64_t> offline_3::maxcut_solver::get_maxcut(const offline_3::graph &graph)
{
    int64_t best_maxcut_weight = INT64_MIN;
    int64_t best_maxcut_weight_pre_search = 0;
    uint64_t total_local_search_iterations = 0;

    for(size_t i = 0; i < iteration_count; ++i)
    {
        offline_3::maxcut maxcut = get_greedy_maxcut(graph);
        int64_t weight_pre_search = get_cut_weight(graph, maxcut.first, maxcut.second);
        total_local_search_iterations += local_search_optimization(graph, maxcut.first, maxcut.second);
        int64_t weight = get_cut_weight(graph, maxcut.first, maxcut.second);

        if(weight > best_maxcut_weight)
        {
            best_maxcut_weight = weight;
            best_maxcut_weight_pre_search = weight_pre_search;
        }
    }

    uint64_t average_local_search_iterations = total_local_search_iterations / iteration_count;

    return {best_maxcut_weight, best_maxcut_weight_pre_search, average_local_search_iterations};
}

offline_3::maxcut offline_3::maxcut_solver::get_greedy_maxcut(const offline_3::graph &graph)
{
    double_t alpha = 1.0;

    if(greedy_level == 0)
    {
        alpha = 0.0;
    }
    else if(greedy_level == 1)
    {
        alpha = (double_t)prng_engine() / std::mt19937_64::max();
    }

    offline_3::edge lightest_edge = graph.get_lightest_edge();
    offline_3::edge heaviest_edge = graph.get_heaviest_edge();
    int64_t weight_min = lightest_edge.get_weight();
    int64_t weight_max = heaviest_edge.get_weight();
    int64_t mu = weight_min + alpha * (weight_max - weight_min);
    std::vector<offline_3::edge> restricted_candidate_list = graph.get_restricted_candidate_edge_list(mu);
    size_t candidate_index = prng_engine() % restricted_candidate_list.size();
    
    std::set<uint64_t> set_x;
    std::set<uint64_t> set_y;

    set_x.insert(restricted_candidate_list[candidate_index].get_from());
    set_y.insert(restricted_candidate_list[candidate_index].get_to());

    const std::set<uint64_t> &graph_vertices_set = graph.get_vertices_id_set();
    std::set<uint64_t> subtracted_set = graph_vertices_set;
    std::set<uint64_t> united_set;

    united_set.insert(restricted_candidate_list[candidate_index].get_from());
    united_set.insert(restricted_candidate_list[candidate_index].get_to());
    subtracted_set.erase(restricted_candidate_list[candidate_index].get_from());
    subtracted_set.erase(restricted_candidate_list[candidate_index].get_to());

    while(true)
    {
        if(united_set == graph_vertices_set)
        {
            break;
        }
        
        std::vector<int64_t> sigma_x(graph.get_vertices_count() + 1, 0);
        std::vector<int64_t> sigma_y(graph.get_vertices_count() + 1, 0);
        int64_t sigma_x_min = INT64_MAX;
        int64_t sigma_x_max = INT64_MIN;
        int64_t sigma_y_min = INT64_MAX;
        int64_t sigma_y_max = INT64_MIN;

        for(std::set<uint64_t>::iterator iterator_subtracted = subtracted_set.begin(); iterator_subtracted != subtracted_set.end(); ++iterator_subtracted)
        {
            int64_t sigma_x_value = 0;
            int64_t sigma_y_value = 0;

            for(std::set<uint64_t>::iterator iterator_y = set_y.begin(); iterator_y != set_y.end(); ++iterator_y)
            {
                sigma_x_value += graph.get_weight(*iterator_subtracted, *iterator_y);
            }

            for(std::set<uint64_t>::iterator iterator_x = set_x.begin(); iterator_x != set_x.end(); ++iterator_x)
            {
                sigma_y_value += graph.get_weight(*iterator_subtracted, *iterator_x);
            }

            sigma_x_min = std::min(sigma_x_min, sigma_x_value);
            sigma_x_max = std::max(sigma_x_max, sigma_x_value);
            sigma_y_min = std::min(sigma_y_min, sigma_y_value);
            sigma_y_max = std::max(sigma_y_max, sigma_y_value);
            sigma_x[*iterator_subtracted] = sigma_x_value;
            sigma_y[*iterator_subtracted] = sigma_y_value;
        }

        weight_min = std::min(sigma_x_min, sigma_y_min);
        weight_max = std::max(sigma_x_max, sigma_y_max);
        mu = weight_min + alpha * (weight_max - weight_min);
        
        std::vector<uint64_t> restricted_candidate_vertex_list;

        for(std::set<uint64_t>::iterator iterator_subtracted = subtracted_set.begin(); iterator_subtracted != subtracted_set.end(); ++iterator_subtracted)
        {
            if(std::max(sigma_x[*iterator_subtracted], sigma_y[*iterator_subtracted]) >= mu)
            {
                restricted_candidate_vertex_list.push_back(*iterator_subtracted);
            }
        }

        candidate_index = prng_engine() % restricted_candidate_vertex_list.size();
        uint64_t random_candidate_id = restricted_candidate_vertex_list[candidate_index];

        if(sigma_x[random_candidate_id] > sigma_y[random_candidate_id])
        {
            set_x.insert(random_candidate_id);
        }
        else
        {
            set_y.insert(random_candidate_id);
        }

        united_set.insert(random_candidate_id);
        subtracted_set.erase(random_candidate_id);
    }

    return {set_x, set_y};
}

uint64_t offline_3::maxcut_solver::local_search_optimization(const offline_3::graph &graph, std::set<uint64_t> &vertices_set1, std::set<uint64_t> &vertices_set2)
{
    bool change = true;
    uint64_t local_search_iterations = 0;

    while(change)
    {
        ++local_search_iterations;
        change = false;
        const std::set<uint64_t> &graph_vertices_set = graph.get_vertices_id_set();

        for(std::set<uint64_t>::iterator iterator = graph_vertices_set.begin(); !change && iterator != graph_vertices_set.end(); ++iterator)
        {
            int64_t sigma1 = 0;
            int64_t sigma2 = 0;

            for(std::set<uint64_t>::iterator iterator2 = vertices_set2.begin(); iterator2 != vertices_set2.end(); ++iterator2)
            {
                sigma1 += graph.get_weight(*iterator, *iterator2);
            }

            for(std::set<uint64_t>::iterator iterator1 = vertices_set1.begin(); iterator1 != vertices_set1.end(); ++iterator1)
            {
                sigma2 += graph.get_weight(*iterator, *iterator1);
            }

            if(vertices_set1.find(*iterator) != vertices_set1.end() && sigma2 > sigma1)
            {
                vertices_set1.erase(*iterator);
                vertices_set2.insert(*iterator);

                change = true;
            }
            else if(vertices_set2.find(*iterator) != vertices_set2.end() && sigma1 > sigma2)
            {
                vertices_set2.erase(*iterator);
                vertices_set1.insert(*iterator);

                change = true;
            }
        }
    }

    return local_search_iterations;
}

int64_t offline_3::maxcut_solver::get_cut_weight(const offline_3::graph &graph, const std::set<uint64_t> &vertices_set1, const std::set<uint64_t> &vertices_set2)
{
    int64_t weight = 0;

    for(std::set<uint64_t>::iterator iterator1 = vertices_set1.begin(); iterator1 != vertices_set1.end(); ++iterator1)
    {
        for(std::set<uint64_t>::iterator iterator2 = vertices_set2.begin(); iterator2 != vertices_set2.end(); ++iterator2)
        {
            weight += graph.get_weight(*iterator1, *iterator2);
        }
    }

    return weight;
}

void offline_3::maxcut_solver::set_iteration_count(const uint64_t &iteration_count)
{
    offline_3::maxcut_solver::iteration_count = iteration_count;
}

void offline_3::maxcut_solver::set_greedy_level(const uint16_t &greedy_level)
{
    offline_3::maxcut_solver::greedy_level = greedy_level;
}