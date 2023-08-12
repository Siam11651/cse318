#include "graph.hpp"
#include "vertex.hpp"

offline_3::graph::graph(const uint64_t &initial_size)
{
    for(size_t i = 1; i <= initial_size; ++i)
    {
        add_vertex(i);
    }
}

bool offline_3::graph::add_vertex(const uint64_t &id)
{
    offline_3::vertex new_vertex(id);

    if(vertices.find(new_vertex) != vertices.end())
    {
        return false;
    }

    vertices.insert(new_vertex);

    return true;
}

bool offline_3::graph::add_edge(const uint64_t &from, const uint64_t &to, const int64_t &weight)
{
    std::set<offline_3::vertex>::iterator from_iterator = vertices.find(offline_3::vertex(from));
    std::set<offline_3::vertex>::iterator to_iterator = vertices.find(offline_3::vertex(to));

    if(from_iterator == vertices.end() || to_iterator == vertices.end())
    {
        return false;
    }

    if(from_iterator->has_adjacent(to))
    {
        return false;
    }

    from_iterator->insert_adjacent(to_iterator->get_id(), weight);

    return true;
}

offline_3::vertex offline_3::graph::get_vertex(const uint64_t &id) const
{
    std::set<offline_3::vertex>::iterator vertex_iterator = vertices.find(offline_3::vertex(id));

    if(vertex_iterator == vertices.end())
    {
        return offline_3::vertex(0);
    }

    return *vertex_iterator;
}

offline_3::edge offline_3::graph::get_heaviest_edge() const
{
    int64_t max_weight = INT64_MIN;
    std::pair<uint64_t, uint64_t> heaviest_edge = {0, 0};

    for(std::set<offline_3::vertex>::iterator iterator = vertices.begin(); iterator != vertices.end(); ++iterator)
    {
        std::pair<uint64_t, int64_t> heaviest_adjacent = iterator->get_heaviest_adjacent();

        if(heaviest_adjacent.second > max_weight)
        {
            max_weight = heaviest_adjacent.second;
            heaviest_edge = {iterator->get_id(), heaviest_adjacent.first};
        }
    }

    return offline_3::edge(heaviest_edge.first, heaviest_edge.second, max_weight);
}

offline_3::edge offline_3::graph::get_lightest_edge() const
{
    int64_t min_weight = INT64_MAX;
    std::pair<uint64_t, uint64_t> lightest_edge = {0, 0};

    for(std::set<offline_3::vertex>::iterator iterator = vertices.begin(); iterator != vertices.end(); ++iterator)
    {
        std::pair<uint64_t, int64_t> lightest_adjacent = iterator->get_lightest_adjacent();

        if(lightest_adjacent.second < min_weight)
        {
            min_weight = lightest_adjacent.second;
            lightest_edge = {iterator->get_id(), lightest_adjacent.first};
        }
    }

    return offline_3::edge(lightest_edge.first, lightest_edge.second, min_weight);
}

std::vector<offline_3::edge> offline_3::graph::get_restricted_candidate_edge_list(const int64_t &mu) const
{
    std::vector<offline_3::edge> rcl;

    for(std::set<offline_3::vertex>::iterator iterator = vertices.begin(); iterator != vertices.end(); ++iterator)
    {
        std::vector<std::pair<uint64_t, int64_t>> ral = iterator->get_restricted_adjacent_list(mu);

        for(size_t i = 0; i < ral.size(); ++i)
        {
            if(ral[i].second <= mu)
            {
                offline_3::edge new_edge(iterator->get_id(), ral[i].first, ral[i].second);

                rcl.push_back(new_edge);
            }
        }
    }

    return rcl;
}

std::set<uint64_t> offline_3::graph::get_vertices_id_set() const
{
    std::set<uint64_t> to_return;

    for(std::set<offline_3::vertex>::iterator iterator = vertices.begin(); iterator != vertices.end(); ++iterator)
    {
        to_return.insert(iterator->get_id());
    }

    return to_return;
}

void offline_3::graph::clear()
{
    vertices.clear();
}