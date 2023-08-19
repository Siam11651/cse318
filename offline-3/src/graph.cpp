#include "graph.hpp"
#include "edge.hpp"

offline_3::graph::graph(const uint64_t &vertices_count)
{
    this->vertices_count = vertices_count;
    adjacency_matrix.assign(vertices_count * vertices_count, 0);

    for(uint64_t i = 1; i <= vertices_count; ++i)
    {
        vertices_set.insert(i);
    }
}

void offline_3::graph::add_edge(const uint64_t &from, const uint64_t &to, const int64_t &weight)
{
    adjacency_matrix[(from - 1) * vertices_count + to - 1] = weight;
    adjacency_matrix[(to - 1) * vertices_count + from - 1] = weight;

    edge_list.push_back(offline_3::edge(from, to, weight));
}

int64_t offline_3::graph::get_weight(const uint64_t &from, const uint64_t &to) const
{
    return adjacency_matrix[(from - 1) * vertices_count + to - 1];
}

offline_3::edge offline_3::graph::get_heaviest_edge() const
{
    offline_3::edge heaviest_edge(0, 0, INT16_MIN);
    // size_t index = 0;

    // for(std::vector<int64_t>::const_iterator iterator = adjacency_matrix.begin(); iterator != adjacency_matrix.end(); ++iterator)
    // {
    //     if(*iterator > heaviest_edge.get_weight())
    //     {
    //         uint64_t from = index / vertices_count + 1;
    //         uint64_t to = index % vertices_count + 1;
    //         int64_t weight = heaviest_edge.get_weight();
    //         heaviest_edge = offline_3::edge(from, to, weight);
    //     }

    //     ++index;
    // }

    for(std::vector<offline_3::edge>::const_iterator iterator = edge_list.begin(); iterator != edge_list.end(); ++iterator)
    {
        heaviest_edge = std::max(heaviest_edge, *iterator);
    }

    return heaviest_edge;
}

offline_3::edge offline_3::graph::get_lightest_edge() const
{
    offline_3::edge lightest_edge(0, 0, INT64_MAX);

    for(std::vector<offline_3::edge>::const_iterator iterator = edge_list.begin(); iterator != edge_list.end(); ++iterator)
    {
        lightest_edge = std::min(lightest_edge, *iterator);
    }

    return lightest_edge;
}

std::vector<offline_3::edge> offline_3::graph::get_restricted_candidate_edge_list(const int64_t &mu) const
{
    std::vector<offline_3::edge> rcl;

    for(std::vector<offline_3::edge>::const_iterator iterator = edge_list.begin(); iterator != edge_list.end(); ++iterator)
    {
        if(iterator->get_weight() >= mu)
        {
            rcl.push_back(*iterator);
        }
    }

    return rcl;
}

const std::set<uint64_t> &offline_3::graph::get_vertices_id_set() const
{
    return vertices_set;
}

uint64_t offline_3::graph::get_vertices_count() const
{
    return vertices_count;
}