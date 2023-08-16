#include "graph.hpp"
#include "edge.hpp"

offline_3::graph::graph(const uint64_t &vertices_count)
{
    this->vertices_count = vertices_count;
    adjacency_matrix.assign(vertices_count * vertices_count, 0);
}

void offline_3::graph::add_edge(const uint64_t &from, const uint64_t &to, const int64_t &weight)
{
    adjacency_matrix[(from - 1) * vertices_count + to - 1] = weight;
}

int64_t offline_3::graph::get_weight(const uint64_t &from, const uint64_t &to) const
{
    return adjacency_matrix[(from - 1) * vertices_count + to - 1];
}

offline_3::edge offline_3::graph::get_heaviest_edge() const
{
    offline_3::edge heaviest_edge(0, 0, INT16_MIN);
    size_t index = 0;

    for(std::vector<int64_t>::const_iterator iterator = adjacency_matrix.begin(); iterator != adjacency_matrix.end(); ++iterator)
    {
        if(*iterator > heaviest_edge.get_weight())
        {
            uint64_t from = index / vertices_count + 1;
            uint64_t to = index % vertices_count + 1;
            int64_t weight = heaviest_edge.get_weight();
            heaviest_edge = offline_3::edge(from, to, weight);
        }

        ++index;
    }

    return heaviest_edge;
}

offline_3::edge offline_3::graph::get_lightest_edge() const
{
    offline_3::edge lightest_edge(0, 0, INT64_MAX);
    size_t index = 0;

    for(std::vector<int64_t>::const_iterator iterator = adjacency_matrix.begin(); iterator != adjacency_matrix.end(); ++iterator)
    {
        if(*iterator > lightest_edge.get_weight())
        {
            uint64_t from = index / vertices_count + 1;
            uint64_t to = index % vertices_count + 1;
            int64_t weight = lightest_edge.get_weight();
            lightest_edge = offline_3::edge(from, to, weight);
        }

        ++index;
    }

    return lightest_edge;
}

std::vector<offline_3::edge> offline_3::graph::get_restricted_candidate_edge_list(const int64_t &mu) const
{
    std::vector<offline_3::edge> rcl;
    size_t index = 0;

    for(std::vector<int64_t>::const_iterator iterator = adjacency_matrix.begin(); iterator != adjacency_matrix.end(); ++iterator)
    {
        if(*iterator >= mu)
        {
            uint64_t from = index / vertices_count + 1;
            uint64_t to = index % vertices_count + 1;

            rcl.push_back(offline_3::edge(from, to, *iterator));
        }

        ++index;
    }

    return rcl;
}

std::set<uint64_t> offline_3::graph::get_vertices_id_set() const
{
    std::set<uint64_t> to_return;

    for(uint64_t i = 1; i <= vertices_count; ++i)
    {
        to_return.insert(i);
    }

    return to_return;
}

uint64_t offline_3::graph::get_vertices_count() const
{
    return vertices_count;
}