#include "graph.hpp"
#include "vertex.hpp"
#include "edge.hpp"

offline_3::graph::graph(const uint64_t &initial_size)
{
    for(size_t i = 0; i < initial_size; ++i)
    {
        vertices.push_back(offline_3::vertex(i + 1));
    }
}

bool offline_3::graph::add_edge(const uint64_t &from, const uint64_t &to, const int64_t &weight)
{
    if(from > vertices.size() || to > vertices.size())
    {
        return false;
    }

    offline_3::vertex &from_vertex = vertices[from - 1];
    offline_3::vertex &to_vertex = vertices[to - 1];

    if(from_vertex.has_adjacent(to))
    {
        return false;
    }

    from_vertex.insert_adjacent(to, weight);

    return true;
}

const offline_3::vertex &offline_3::graph::get_vertex(const uint64_t &id) const
{
    return vertices[id - 1];
}

offline_3::edge offline_3::graph::get_heaviest_edge() const
{
    offline_3::edge heaviest_edge(0, 0, INT16_MIN);

    for(std::vector<offline_3::vertex>::const_iterator iterator = vertices.begin(); iterator != vertices.end(); ++iterator)
    {
        offline_3::edge heaviest_adjacent = iterator->get_heaviest_adjacent();

        if(heaviest_adjacent.get_weight() > heaviest_edge.get_weight())
        {
            heaviest_edge = offline_3::edge(iterator->get_id(), heaviest_adjacent.get_to(), heaviest_adjacent.get_weight());
        }
    }

    return heaviest_edge;
}

offline_3::edge offline_3::graph::get_lightest_edge() const
{
    offline_3::edge lightest_edge(0, 0, INT64_MAX);

    for(std::vector<offline_3::vertex>::const_iterator iterator = vertices.begin(); iterator != vertices.end(); ++iterator)
    {
        offline_3::edge lightest_adjacent = iterator->get_lightest_adjacent();

        if(lightest_adjacent.get_weight() < lightest_edge.get_weight())
        {
            lightest_edge = offline_3::edge(iterator->get_id(), lightest_adjacent.get_to(), lightest_adjacent.get_weight());
        }
    }

    return lightest_edge;
}

std::vector<offline_3::edge> offline_3::graph::get_restricted_candidate_edge_list(const int64_t &mu) const
{
    std::vector<offline_3::edge> rcl;

    for(std::vector<offline_3::vertex>::const_iterator iterator = vertices.begin(); iterator != vertices.end(); ++iterator)
    {
        std::vector<offline_3::edge> ral = iterator->get_restricted_adjacent_list(mu);

        for(size_t i = 0; i < ral.size(); ++i)
        {
            if(ral[i].get_weight() >= mu)
            {
                offline_3::edge new_edge(iterator->get_id(), ral[i].get_to(), ral[i].get_weight());

                rcl.push_back(new_edge);
            }
        }
    }

    return rcl;
}

std::set<uint64_t> offline_3::graph::get_vertices_id_set() const
{
    std::set<uint64_t> to_return;

    for(std::vector<offline_3::vertex>::const_iterator iterator = vertices.begin(); iterator != vertices.end(); ++iterator)
    {
        to_return.insert(iterator->get_id());
    }

    return to_return;
}

uint64_t offline_3::graph::get_vertices_count() const
{
    return vertices.size();
}